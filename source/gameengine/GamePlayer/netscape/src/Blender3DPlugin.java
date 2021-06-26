//
// $Id: Blender3DPlugin.java 15444 2008-07-05 17:05:05Z lukep $
// Copyright (C) 2001 NaN Technologies B.V.
// Java peer class for the plugin. This provides access for 
// javascript users through JRI. 
//


import netscape.plugin.Plugin;

class Blender3DPlugin extends Plugin {
  /**
   * Send a message to the currently running gameengine.
   */
    public native void SendMessage(String to, 
				   String from , 
				   String subject, 
				   String body);

  /**
   * Restart with a new url.
   */
    public native void blenderURL(String url);
}


