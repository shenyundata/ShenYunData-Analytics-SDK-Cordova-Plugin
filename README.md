
#ShenYunData-Analytics-SDK-Cordova-Plugin集成文档

##适用范围

ShenYunData-Analytics-SDK-Cordova-Plugin 适用于 Cordova 和 PhoneGap 跨平台项目。
     
##集成方式

1.	下载项目到本地目录：

    `git clone https://github.com/shenyundata/ShenYunData-Analytics-SDK-Cordova-Plugin.git`  
     
2.   访问http://www.shenyundata.com/ 下载最新版本的 Android 和 iOS 平台 Analytics SDK。Plugin 中的 SDK 可能不是最新版本，需要检查并使用刚刚下载的新版本，进入克隆到本地的 Plugin 目录：

     `Android 平台` 
     
     `使用最新版本 SDK 的 jar 包替换 Plugin 中的 src\android\ShenYunStatistics_Android.jar 文件。`

     `iOS 平台`
     
     `使用最新版本 SDK 的 .h 头文件, .a 静态库文件和.bundle替换 Plugin 中 src\ios 文件夹下的同名文件。` 
      `关于ATS的说明
	如果你的app基于9.0编译，那么为了适配iOS9.0的APP Transport Security(ATS)对http的限制，需要对SDK的请求地址shenyundata.com做例外，在app对应的info.list中添加如下配置。         
	<key>NSAppTransportSecurity</key>
    <dict>
       <key>NSExceptionDomains</key>
       <dict>
        <key>shenyundata.com</key>
        <dict>
        <key>NSIncludesSubdomains</key>
        <true/>
        <key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
        <true/>
        <key>NSTemporaryExceptionMinimumTLSVersion</key>
        <string>TLSv1.0</string>
        <key>NSTemporaryExceptionRequiresForwardSecrecy</key>
        <false/>
        </dict>
   	 </dict>
	</dict>


	说明：
	如果用户做了如下配置：
         
	<key>NSAppTransportSecurity</key>
  	  <dict>    
        <key>NSAllowsArbitraryLoads</key><true/>
    </dict>
	上述NSAppTransportSecurity可以不配置 `
 
3. 	进入 Cordova 工程目录，执行下面的命令添加 Plugin

    `cordova plugin add "[Plugin 路径]"` 
   
4. 	访问 http://www.shenyundata.com/  注册帐号并按照提示申请 appKey。 
5. 	使用申请到的 appKey在 Cordova 工程的 Native 代码中集成 SDK 并初始化。      
	如果已经在js中调用ShenYunData.init("[Your appKey]", "[Your channel]" , "[Your subChannel]");则无需调用以下native初始化方法。
       - Android平台   
        在继承自 CordovaActivity 类型的 JAVA 类文件，比如 %Cordova工程目录`%\platforms\android\src\com\shenyun\analysisdemo\MainActivity.java`中，找到 onCreate 方法，加入下面的初始化代码：   
        `ShenYunCordovaStatistics.init(this, "[Your appKey]", "[Your channel]" , "[Your subChannel]");
 [Your appKey]` 就是刚刚申请的 `appKey，[Your Channel] `是应用的渠道号, `[Your subChannel]` 是应用的子渠道号,
	
	测试SDK，对集成进行测试时请在程序入口处调用以下代码：   `ShenYunCordovaStatistics.setDevMode(this, true)`;

       - iOS平台   
       注意：静态库中采用ObjectC++实现，因此需要您保证您工程中至少有一个.mm后缀的源文件(您可以将任意一个.m后缀的文件改名为.mm，例如AppDelegate.m改为AppDelegate.mm)，或者在工程属性中指定编译方式，即在Xcode的Project -> Edit Active Target -> Build Setting 中找到 Compile Sources As，并将其设置为"Objective-C++"  - 注意：  该版本中需要通过定位功能来标识信息的地域性特征，需要在(工程名)-Info.plist文件里进行配置NSLocationWhenInUseUsageDescription。所对应的value会在向用户请求该种类型定位授权的时候作为提示语显示出来，该value可自定义。        
       在Cordova工程目录/platforms/ios/demo/Classes/AppDelegate.m 文件中，找到方法(BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions，添加下面的代码：   
setDevMode 区分测试与正式数据，YES为测试数据	   
`[ShenYun_StatisticsSDK setDevMode:YES];`              
`[ShenYun_StatisticsSDK startWithAppKey:@"4028804a54be207f0154c87118f80003" channel:@"AppStore" 
subChannel:@""];`
     
      
   
      
     
     
          
  
          
6. 	编译工程：
     
     `cordova build`
    
    
    
    
##接口说明

ShenYunData.js 文件中定义了下面的接口：



	
    /**
     * 初始化 ShenYunData Analytics SDK appKey、渠道、子渠道等，该方法应该在程序入口处调用。
     * 以下3个参数的顺序不能乱
     *
     * @param {String} appKey, the app's appKey
     * @param {String} appChannel, 应用渠道
     * @param {String} appSubChannel, 应用子渠道
     */
	init: function(appKey, appChannel, appSubChannel) {
        cordova.exec(null, null, "ShenYunData", "init", [appKey, appChannel, appSubChannel]);
    },

    /**
     * 进入页面时调用该方法，与onPageEnd(pageName)必须成对调用
     *
     * @param {String} pageName             current page name
     *
     */
    onPageStart: function(pageName) {
        cordova.exec(null, null, "ShenYunData", "onPageStart", [pageName]);
    },

    /**
     * 在离开页面时调用该方法，与onPageStart(pageName)必须成对调用
     *
     *  @param {String} pageName             current page name
     */
    onPageEnd: function(pageName) {
        cordova.exec(null, null, "ShenYunData", "onPageEnd", [pageName]);
    },

    /**
     * 保存用户事件信息，如登录，购买，支付等.

      * 以下四个参数的顺序不能乱，其它附加参数封装在第四个参数params中，顺序任意，参数任意，但要以键值对的形式成对传递。
     *
     * @param {String} userId, the logon userId
     * @param {String} eventAction, 用户的行为名称，如place_order, purchase等，
     *       来源有两种，一种是参考文档中EventAction中的枚举采用小写形式，一种是用户在web端注册的，任意填写的不做分析、展示
     * @param {String} status, 用户行为状态，一般为click, success, fail
     * @param {String} params, json object contains all params in key:value ex: {"amount": "2000", "price": "500.0", "quantity":"4"}
     */
     onEvent: function(userId, eventAction, status, params) {
        cordova.exec(null, null, "ShenYunData", "onEvent", [userId, eventAction, status, params]);
    }


   在项目的 JS 代码中调用时，可参考上面的接口说明和下面的调用方式进行：

   

   自定义事件：   
`ShenYunData.onEvent(userId, eventAction, status, params) `      
记录某个页面的启动，在页面加载完毕时调用：      
`ShenYunData.onPageStart('This is page name') `   
记录某个页面的消失，在页面即将消失时调用：       
`ShenYunData.onPageEnd('This is the same name as in onPageStart Api') `   
需要注意的是，onPageStart 和 onPageEnd 应该成对调用，用来记录一个特定页面的活跃时间。

   

##Demo

下面的 Demo 中演示了不同平台上的集成方式，包括 Demo 的创建过程：

1.	 [ShenYunData-Analytics-SDK-Cordova-Android-Demo](https://github.com/shenyundata/ShenYunData-Analytics-SDK-Cordova-Android-Demo "a Safari extension").
2.	[ShenYunData-Analytics-SDK-Cordova-iOS-Demo](https://github.com/shenyundata/ShenYunData-Analytics-SDK-Cordova-iOS-Demo "a Safari extension").


















    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
