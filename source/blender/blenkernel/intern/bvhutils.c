/**
 *
 * $Id: bvhutils.c 19744 2009-04-15 19:33:25Z jaguarandi $
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): André Pinto.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "BKE_bvhutils.h"

#include "DNA_object_types.h"
#include "DNA_modifier_types.h"
#include "DNA_meshdata_types.h"

#include "BKE_DerivedMesh.h"
#include "BKE_utildefines.h"
#include "BKE_deform.h"
#include "BKE_cdderivedmesh.h"
#include "BKE_displist.h"
#include "BKE_global.h"

#include "BLI_arithb.h"
#include "BLI_linklist.h"
#include "MEM_guardedalloc.h"

/* Math stuff for ray casting on mesh faces and for nearest surface */

static float ray_tri_intersection(const BVHTreeRay *ray, const float m_dist, const float *v0, const float *v1, const float *v2)
{
	float dist;

	if(RayIntersectsTriangle((float*)ray->origin, (float*)ray->direction, (float*)v0, (float*)v1, (float*)v2, &dist, NULL))
		return dist;

	return FLT_MAX;
}

static float sphereray_tri_intersection(const BVHTreeRay *ray, float radius, const float m_dist, const float *v0, const float *v1, const float *v2)
{
	
	float idist;
	float p1[3];
	float plane_normal[3], hit_point[3];

	CalcNormFloat((float*)v0, (float*)v1, (float*)v2, plane_normal);

	VECADDFAC( p1, ray->origin, ray->direction, m_dist);
	if(SweepingSphereIntersectsTriangleUV((float*)ray->origin, p1, radius, (float*)v0, (float*)v1, (float*)v2, &idist, hit_point))
	{
		return idist * m_dist;
	}

	return FLT_MAX;
}


/*
 * Function adapted from David Eberly's distance tools (LGPL)
 * http://www.geometrictools.com/LibFoundation/Distance/Distance.html
 */
static float nearest_point_in_tri_surface(const float *v0,const float *v1,const float *v2,const float *p, int *v, int *e, float *nearest )
{
	float diff[3];
	float e0[3];
	float e1[3];
	float A00;
	float A01;
	float A11;
	float B0;
	float B1;
	float C;
	float Det;
	float S;
	float T;
	float sqrDist;
	int lv = -1, le = -1;
	
	VECSUB(diff, v0, p);
	VECSUB(e0, v1, v0);
	VECSUB(e1, v2, v0);
	
	A00 = INPR ( e0, e0 );
	A01 = INPR( e0, e1 );
	A11 = INPR ( e1, e1 );
	B0 = INPR( diff, e0 );
	B1 = INPR( diff, e1 );
	C = INPR( diff, diff );
	Det = fabs( A00 * A11 - A01 * A01 );
	S = A01 * B1 - A11 * B0;
	T = A01 * B0 - A00 * B1;

	if ( S + T <= Det )
	{
		if ( S < 0.0f )
		{
			if ( T < 0.0f )  // Region 4
			{
				if ( B0 < 0.0f )
				{
					T = 0.0f;
					if ( -B0 >= A00 )
					{
						S = (float)1.0;
						sqrDist = A00 + 2.0f * B0 + C;
						lv = 1;
					}
					else
					{
						if(fabs(A00) > FLT_EPSILON)
							S = -B0/A00;
						else
							S = 0.0f;
						sqrDist = B0 * S + C;
						le = 0;
					}
				}
				else
				{
					S = 0.0f;
					if ( B1 >= 0.0f )
					{
						T = 0.0f;
						sqrDist = C;
						lv = 0;
					}
					else if ( -B1 >= A11 )
					{
						T = 1.0f;
						sqrDist = A11 + 2.0f * B1 + C;
						lv = 2;
					}
					else
					{
						if(fabs(A11) > FLT_EPSILON)
							T = -B1 / A11;
						else
							T = 0.0f;
						sqrDist = B1 * T + C;
						le = 1;
					}
				}
			}
			else  // Region 3
			{
				S = 0.0f;
				if ( B1 >= 0.0f )
				{
					T = 0.0f;
					sqrDist = C;
					lv = 0;
				}
				else if ( -B1 >= A11 )
				{
					T = 1.0f;
					sqrDist = A11 + 2.0f * B1 + C;
					lv = 2;
				}
				else
				{
					if(fabs(A11) > FLT_EPSILON)
						T = -B1 / A11;
					else
						T = 0.0;
					sqrDist = B1 * T + C;
					le = 1;
				}
			}
		}
		else if ( T < 0.0f )  // Region 5
		{
			T = 0.0f;
			if ( B0 >= 0.0f )
			{
				S = 0.0f;
				sqrDist = C;
				lv = 0;
			}
			else if ( -B0 >= A00 )
			{
				S = 1.0f;
				sqrDist = A00 + 2.0f * B0 + C;
				lv = 1;
			}
			else
			{
				if(fabs(A00) > FLT_EPSILON)
					S = -B0 / A00;
				else
					S = 0.0f;
				sqrDist = B0 * S + C;
				le = 0;
			}
		}
		else  // Region 0
		{
            // Minimum at interior lv
			float invDet;
			if(fabs(Det) > FLT_EPSILON)
				invDet = 1.0f / Det;
			else
				invDet = 0.0f;
			S *= invDet;
			T *= invDet;
			sqrDist = S * ( A00 * S + A01 * T + 2.0f * B0) +
					T * ( A01 * S + A11 * T + 2.0f * B1 ) + C;
		}
	}
	else
	{
		float tmp0, tmp1, numer, denom;

		if ( S < 0.0f )  // Region 2
		{
			tmp0 = A01 + B0;
			tmp1 = A11 + B1;
			if ( tmp1 > tmp0 )
			{
				numer = tmp1 - tmp0;
				denom = A00 - 2.0f * A01 + A11;
				if ( numer >= denom )
				{
					S = 1.0f;
					T = 0.0f;
					sqrDist = A00 + 2.0f * B0 + C;
					lv = 1;
				}
				else
				{
					if(fabs(denom) > FLT_EPSILON)
						S = numer / denom;
					else
						S = 0.0f;
					T = 1.0f - S;
					sqrDist = S * ( A00 * S + A01 * T + 2.0f * B0 ) +
							T * ( A01 * S + A11 * T + 2.0f * B1 ) + C;
					le = 2;
				}
			}
			else
			{
				S = 0.0f;
				if ( tmp1 <= 0.0f )
				{
					T = 1.0f;
					sqrDist = A11 + 2.0f * B1 + C;
					lv = 2;
				}
				else if ( B1 >= 0.0f )
				{
					T = 0.0f;
					sqrDist = C;
					lv = 0;
				}
				else
				{
					if(fabs(A11) > FLT_EPSILON)
						T = -B1 / A11;
					else
						T = 0.0f;
					sqrDist = B1 * T + C;
					le = 1;
				}
			}
		}
		else if ( T < 0.0f )  // Region 6
		{
			tmp0 = A01 + B1;
			tmp1 = A00 + B0;
			if ( tmp1 > tmp0 )
			{
				numer = tmp1 - tmp0;
				denom = A00 - 2.0f * A01 + A11;
				if ( numer >= denom )
				{
					T = 1.0f;
					S = 0.0f;
					sqrDist = A11 + 2.0f * B1 + C;
					lv = 2;
				}
				else
				{
					if(fabs(denom) > FLT_EPSILON)
						T = numer / denom;
					else
						T = 0.0f;
					S = 1.0f - T;
					sqrDist = S * ( A00 * S + A01 * T + 2.0f * B0 ) +
							T * ( A01 * S + A11 * T + 2.0f * B1 ) + C;
					le = 2;
				}
			}
			else
			{
				T = 0.0f;
				if ( tmp1 <= 0.0f )
				{
					S = 1.0f;
					sqrDist = A00 + 2.0f * B0 + C;
					lv = 1;
				}
				else if ( B0 >= 0.0f )
				{
					S = 0.0f;
					sqrDist = C;
					lv = 0;
				}
				else
				{
					if(fabs(A00) > FLT_EPSILON)
						S = -B0 / A00;
					else
						S = 0.0f;
					sqrDist = B0 * S + C;
					le = 0;
				}
			}
		}
		else  // Region 1
		{
			numer = A11 + B1 - A01 - B0;
			if ( numer <= 0.0f )
			{
				S = 0.0f;
				T = 1.0f;
				sqrDist = A11 + 2.0f * B1 + C;
				lv = 2;
			}
			else
			{
				denom = A00 - 2.0f * A01 + A11;
				if ( numer >= denom )
				{
					S = 1.0f;
					T = 0.0f;
					sqrDist = A00 + 2.0f * B0 + C;
					lv = 1;
				}
				else
				{
					if(fabs(denom) > FLT_EPSILON)
						S = numer / denom;
					else
						S = 0.0f;
					T = 1.0f - S;
					sqrDist = S * ( A00 * S + A01 * T + 2.0f * B0 ) +
							T * ( A01 * S + A11 * T + 2.0f * B1 ) + C;
					le = 2;
				}
			}
		}
	}

	// Account for numerical round-off error
	if ( sqrDist < FLT_EPSILON )
		sqrDist = 0.0f;
	
	{
		float w[3], x[3], y[3], z[3];
		VECCOPY(w, v0);
		VECCOPY(x, e0);
		VecMulf(x, S);
		VECCOPY(y, e1);
		VecMulf(y, T);
		VECADD(z, w, x);
		VECADD(z, z, y);
		//VECSUB(d, p, z);
		VECCOPY(nearest, z);
		// d = p - ( v0 + S * e0 + T * e1 );
	}
	*v = lv;
	*e = le;

	return sqrDist;
}


/*
 * BVH from meshs callbacks
 */

// Callback to bvh tree nearest point. The tree must bust have been built using bvhtree_from_mesh_faces.
// userdata must be a BVHMeshCallbackUserdata built from the same mesh as the tree.
static void mesh_faces_nearest_point(void *userdata, int index, const float *co, BVHTreeNearest *nearest)
{
	const BVHTreeFromMesh *data = (BVHTreeFromMesh*) userdata;
	MVert *vert	= data->vert;
	MFace *face = data->face + index;

	float *t0, *t1, *t2, *t3;
	t0 = vert[ face->v1 ].co;
	t1 = vert[ face->v2 ].co;
	t2 = vert[ face->v3 ].co;
	t3 = face->v4 ? vert[ face->v4].co : NULL;

	
	do
	{	
		float nearest_tmp[3], dist;
		int vertex, edge;
		
		dist = nearest_point_in_tri_surface(t0, t1, t2, co, &vertex, &edge, nearest_tmp);
		if(dist < nearest->dist)
		{
			nearest->index = index;
			nearest->dist = dist;
			VECCOPY(nearest->co, nearest_tmp);
			CalcNormFloat(t0, t1, t2, nearest->no);
		}

		t1 = t2;
		t2 = t3;
		t3 = NULL;

	} while(t2);
}

// Callback to bvh tree raycast. The tree must bust have been built using bvhtree_from_mesh_faces.
// userdata must be a BVHMeshCallbackUserdata built from the same mesh as the tree.
static void mesh_faces_spherecast(void *userdata, int index, const BVHTreeRay *ray, BVHTreeRayHit *hit)
{
	const BVHTreeFromMesh *data = (BVHTreeFromMesh*) userdata;
	MVert *vert	= data->vert;
	MFace *face = data->face + index;

	float *t0, *t1, *t2, *t3;
	t0 = vert[ face->v1 ].co;
	t1 = vert[ face->v2 ].co;
	t2 = vert[ face->v3 ].co;
	t3 = face->v4 ? vert[ face->v4].co : NULL;

	
	do
	{	
		float dist;
		if(data->sphere_radius == 0.0f)
			dist = ray_tri_intersection(ray, hit->dist, t0, t1, t2);
		else
			dist = sphereray_tri_intersection(ray, data->sphere_radius, hit->dist, t0, t1, t2);

		if(dist >= 0 && dist < hit->dist)
		{
			hit->index = index;
			hit->dist = dist;
			VECADDFAC(hit->co, ray->origin, ray->direction, dist);

			CalcNormFloat(t0, t1, t2, hit->no);
		}

		t1 = t2;
		t2 = t3;
		t3 = NULL;

	} while(t2);
}

/*
 * BVH builders
 */
// Builds a bvh tree.. where nodes are the vertexs of the given mesh
BVHTree* bvhtree_from_mesh_verts(BVHTreeFromMesh *data, DerivedMesh *mesh, float epsilon, int tree_type, int axis)
{
	BVHTree *tree = bvhcache_find(&mesh->bvhCache, BVHTREE_FROM_VERTICES);

	//Not in cache
	if(tree == NULL)
	{
		int i;
		int numVerts= mesh->getNumVerts(mesh);
		MVert *vert	= mesh->getVertDataArray(mesh, CD_MVERT);

		if(vert != NULL)
		{
			tree = BLI_bvhtree_new(numVerts, epsilon, tree_type, axis);

			if(tree != NULL)
			{
				for(i = 0; i < numVerts; i++)
					BLI_bvhtree_insert(tree, i, vert[i].co, 1);

				BLI_bvhtree_balance(tree);

				//Save on cache for later use
//				printf("BVHTree built and saved on cache\n");
				bvhcache_insert(&mesh->bvhCache, tree, BVHTREE_FROM_VERTICES);
			}
		}
	}
	else
	{
//		printf("BVHTree is already build, using cached tree\n");
	}


	//Setup BVHTreeFromMesh
	memset(data, 0, sizeof(*data));
	data->tree = tree;

	if(data->tree)
	{
		data->cached = TRUE;

		//a NULL nearest callback works fine
		//remeber the min distance to point is the same as the min distance to BV of point
		data->nearest_callback = NULL;
		data->raycast_callback = NULL;

		data->mesh = mesh;
		data->vert = mesh->getVertDataArray(mesh, CD_MVERT);
		data->face = mesh->getFaceDataArray(mesh, CD_MFACE);

		data->sphere_radius = epsilon;
	}

	return data->tree;
}

// Builds a bvh tree.. where nodes are the faces of the given mesh.
BVHTree* bvhtree_from_mesh_faces(BVHTreeFromMesh *data, DerivedMesh *mesh, float epsilon, int tree_type, int axis)
{
	BVHTree *tree = bvhcache_find(&mesh->bvhCache, BVHTREE_FROM_FACES);

	//Not in cache
	if(tree == NULL)
	{
		int i;
		int numFaces= mesh->getNumFaces(mesh);
		MVert *vert	= mesh->getVertDataArray(mesh, CD_MVERT);
		MFace *face = mesh->getFaceDataArray(mesh, CD_MFACE);

		if(vert != NULL && face != NULL)
		{
			/* Create a bvh-tree of the given target */
			tree = BLI_bvhtree_new(numFaces, epsilon, tree_type, axis);
			if(tree != NULL)
			{
				for(i = 0; i < numFaces; i++)
				{
					float co[4][3];
					VECCOPY(co[0], vert[ face[i].v1 ].co);
					VECCOPY(co[1], vert[ face[i].v2 ].co);
					VECCOPY(co[2], vert[ face[i].v3 ].co);
					if(face[i].v4)
						VECCOPY(co[3], vert[ face[i].v4 ].co);
			
					BLI_bvhtree_insert(tree, i, co[0], face[i].v4 ? 4 : 3);
				}
				BLI_bvhtree_balance(tree);

				//Save on cache for later use
//				printf("BVHTree built and saved on cache\n");
				bvhcache_insert(&mesh->bvhCache, tree, BVHTREE_FROM_FACES);
			}
		}
	}
	else
	{
//		printf("BVHTree is already build, using cached tree\n");
	}


	//Setup BVHTreeFromMesh
	memset(data, 0, sizeof(*data));
	data->tree = tree;

	if(data->tree)
	{
		data->cached = TRUE;

		data->nearest_callback = mesh_faces_nearest_point;
		data->raycast_callback = mesh_faces_spherecast;

		data->mesh = mesh;
		data->vert = mesh->getVertDataArray(mesh, CD_MVERT);
		data->face = mesh->getFaceDataArray(mesh, CD_MFACE);

		data->sphere_radius = epsilon;
	}
	return data->tree;

}

// Frees data allocated by a call to bvhtree_from_mesh_*.
void free_bvhtree_from_mesh(struct BVHTreeFromMesh *data)
{
	if(data->tree)
	{
		if(!data->cached)
			BLI_bvhtree_free(data->tree);

		memset( data, 0, sizeof(data) );
	}
}


/* BVHCache */
typedef struct BVHCacheItem
{
	int type;
	BVHTree *tree;

} BVHCacheItem;

static void bvhcacheitem_set_if_match(void *_cached, void *_search)
{
	BVHCacheItem * cached = (BVHCacheItem *)_cached;
	BVHCacheItem * search = (BVHCacheItem *)_search;

	if(search->type == cached->type)
	{
		search->tree = cached->tree;		
	}
} 

BVHTree *bvhcache_find(BVHCache *cache, int type)
{
	BVHCacheItem item;
	item.type = type;
	item.tree = NULL;

	BLI_linklist_apply(*cache, bvhcacheitem_set_if_match, &item);
	return item.tree;
}

void bvhcache_insert(BVHCache *cache, BVHTree *tree, int type)
{
	BVHCacheItem *item = NULL;

	assert( tree != NULL );
	assert( bvhcache_find(cache, type) == NULL );

	item = MEM_mallocN(sizeof(BVHCacheItem), "BVHCacheItem");
	assert( item != NULL );

	item->type = type;
	item->tree = tree;

	BLI_linklist_prepend( cache, item );
}


void bvhcache_init(BVHCache *cache)
{
	*cache = NULL;
}

static void bvhcacheitem_free(void *_item)
{
	BVHCacheItem *item = (BVHCacheItem *)_item;

	BLI_bvhtree_free(item->tree);
	MEM_freeN(item);
}


void bvhcache_free(BVHCache *cache)
{
	BLI_linklist_free(*cache, (LinkNodeFreeFP)bvhcacheitem_free);
	*cache = NULL;
}


