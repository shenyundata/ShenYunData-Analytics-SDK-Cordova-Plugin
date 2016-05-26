/*
       Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
*/
package com.shenyun.statistics.plugins;

import android.app.Activity;
import android.webkit.JavascriptInterface;

import com.shenyun.statistics.analysis.ShenYunCordovaStatistics;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;

/**
 * This class provides access to vibration on the device.
 */
public class ShenYunDataPlugin extends CordovaPlugin {

    private Activity activity;

    /**
     * Constructor.
     */
    public ShenYunDataPlugin() {
    }

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        this.activity = cordova.getActivity();
        this.webView = webView;
    }

    /**
     * Executes the request and returns PluginResult.
     *
     * @param action          The action to execute.
     * @param args            JSONArray of arguments for the plugin.
     * @param callbackContext The callback context used when calling back into JavaScript.
     * @return True when the action was valid, false otherwise.
     */
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
		if (action.equals("init")) {
            ShenYunCordovaStatistics.init(activity, args.getString(0), args.getString(1), args.getString(2));
		} else if (action.equals("setDevMode")) {
            ShenYunCordovaStatistics.setDevMode(activity, args.getBoolean(0));
        } else if (action.equals("onPageStart")) {
            ShenYunCordovaStatistics.onResume(activity, args.getString(0));
        } else if (action.equals("onPageEnd")) {
            ShenYunCordovaStatistics.onPause(activity, args.getString(0));
        } else if (action.equals("onEvent")) {
            ShenYunCordovaStatistics.onEvent(activity, args.getString(0), args.getString(1), args.getString(2), args.getString(3));
        } else {
            return false;
        }

        // Only alert and confirm are async.
        callbackContext.success();
        return true;
    }


    //--------------------------------------------------------------------------
    // LOCAL METHODS
    //--------------------------------------------------------------------------

}
