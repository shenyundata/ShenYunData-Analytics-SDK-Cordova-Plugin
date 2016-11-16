
var ShenYunData = {
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
	 * 开发者模式开关,调试时用
	 * @param isDebug 为true则相关数据表示是测试数据，否则是正式数据，默认为false
	 */
    setDevMode: function(isDebug) {
        cordova.exec(null, null, "ShenYunData", "setDevMode", [isDebug]);
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


};

module.exports = ShenYunData;

