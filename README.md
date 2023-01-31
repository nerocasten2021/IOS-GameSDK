# IOS GameSDK

[![Platforms](https://img.shields.io/cocoapods/p/FBSDKCoreKit.svg)]()

**This guide shows you how to integrate your iOS app using the GameSDK for iOS. The GameSDK for iOS consists of the following component SDKs:**
  - The GameSDK Core
  - Thirdparty framework: GoogleSigin SDK, Firebase SDK, Facebook SDK, AppsFlyer SDK
  
### FEATURES:
  - Login: Authenticate people with their my server ID, Google and Facebook credentials.
  - Payment IAP: Pay to buy products from in-app
  - Track Events: Track events with third parties including Appsflyer and Firebase tracking
  - You will need some included keys:Client ID, Facebook App ID, FacebookClient Token and GoogleService-Info.plist file

# Try It Out

* Download [GameSDK latest](https://github.com/nerocasten2021/IOS-GameSDK/releases/) and [Third party framework](https://github.com/nerocasten2021/IOS-GameSDK/releases/) (FacebooSDK, FirebaseSDK, AppsflyerSDK)
* GoogleService-Info.plist: send via mail
* Install the following: App Tracking Transparency framework only available starting from Xcode 12 or later-The SDK supports iOS10+

# Integrate

- Embed GameSDK latest version and Third party framework into your project
- Some other libraries: 
  - AuthenticationServices.framework
  - MediaPlayer.framework
  - MobileCoreServices.framework
  - SystemConfiguration.framework
  - MessageUI.framework
- Adding Capabilities: Sign-in with Apple, Push Notifications

### With Facebook IOS SDK version 13 or latest
  - Create a swift file (arbitrary name), confirm "Create Bridging Header" when prompt appear
  - Add Accelerate.framework to target: Target --> Build Phases --> Link Binary With Libraries --> click Plus, find and add Accelerate.framework
  - Enable Modules (C and Objective-C) set to YES: Target --> Build Settings --> Enable Modules (C and Objective-C)
  
# Configuration
- Insert -ObjC -lc++ -lz to “Other Linker Flags ”on Xcode Project: Main target -> build settings -> search "other linker flags"
- Configure Tracking Usage Description into .plist file (default: info.plist)*.
  Open with source and insert code: 
  ```xml
  <key>NSUserTrackingUsageDescription</key>
  <string>This identifier will be used to deliver personalized ads to you.</string>
  ```
- Configure Client ID into .plist file (default: info.plist)*. IN the <string> tag, key GameClientID will be provided privately via email
```xml
<key>GameClientID</key>
<string>GameClientID</string>
```
### Configure FacebookSDK in your project (default info.plist)
** Refer [Facebook get started](https://developers.facebook.com/docs/ios/getting-started#step-2---configure-your-project) **
```xml
<key>FacebookAppID</key>
<string>FacebookAppID</string>
<key>FacebookClientToken</key>
<string>CLIENT-TOKEN</string>
<key>FacebookDisplayName</key>
<string>FacebookDisplayName</string>
<key>CFBundleURLTypes</key>
<array>
  <dict>
    <key>CFBundleURLSchemes</key>
    <array>
      <string>fbFacebookAppID</string>
    </array>
  </dict>
</array>
<key>LSApplicationQueriesSchemes</key>
<array>
  <string>fbapi</string>
  <string>fbapi20130214</string>
  <string>fbapi20130410</string>
  <string>fbapi20130702</string>
  <string>fbapi20131010</string>
  <string>fbapi20131219</string>
  <string>fbapi20140410</string>
  <string>fbapi20140116</string>
  <string>fbapi20150313</string>
  <string>fbapi20150629</string>
  <string>fbapi20160328</string>
  <string>fbauth</string>
  <string>fb-messenger-share-api</string>
  <string>fbauth2</string>
  <string>fbshareextension</string>
</array>
```
* Replace APP-ID with FacebookApp ID
* In the key FacebookClientToken, replace CLIENT-TOKEN 
* In the key FacebookDisplayName, replaceAPP-NAME with the name of provided.
  
### Configure GoogleSignIn in your project (default info.plist)
  ** Refer [Get started with Google Sign-In for iOS](https://developers.google.com/identity/sign-in/ios/start-integrating) **
  ```xml
   <key>GoogleAppID</key>
   <string>1234567890-abcdefg.apps.googleusercontent.com</string>
   <key>CFBundleURLTypes</key>
   <array>
    <dict>
       <key>CFBundleURLSchemes</key>
       <array>
          <string>com.googleusercontent.apps.1234567890-abcdefg</string>
       </array>
    </dict>
   </array>
  ```
  
### Add services and SDK related resource library
1. The file Appdelegate.m configuration instructions are as follows:
```objectivec
#import "GameSDK.h"
#import <UserNotifications/UserNotifications.h>
@interfaceAppDelegate()<FIRMessagingDelegate, UNUserNotificationCenterDelegate>
@end
```
2. Add openURL
```objectivec
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    if (@available(iOS 9.0, *)) {
        BOOL handled = [[GameSDK sharedInstance] application:application openURL:url options:options];
        return handled;
    } else {
        return YES;
    }
}
```
3. Add didFinishLaunchingWithOption
```objectivec
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //your code
    
    //init SDK
    [[GameSDK sharedInstance] initSdk];
    [[GameSDK sharedInstance] application:application didFinishLaunchingWithOptions:launchOptions];
    [[GameSDK Firebase] application:self andApplication:application didFinishLaunchingWithOptions:launchOptions];
    return YES;
}
```
4. Add applicationDidBecomeActive
```objectivec
- (void)applicationDidBecomeActive:(UIApplication *)application {
    NSLog(@"applicationDidBecomeActive");
    [[GameSDK sharedInstance] applicationDidBecomeActive:application];
    application.applicationIconBadgeNumber = 0;
}
```
5. Add applicationWillTerminate
```objectivec
- (void)applicationWillTerminate:(UIApplication *)application {
    //reset owner billing had payment
    [[GameSDK AppleIAP] terminateIAP];
}
```
6. Registration FCM token and message
```objectivec
- (void)messaging:(FIRMessaging *)messaging didReceiveRegistrationToken:(NSString *)fcmToken {
    [[GameSDK Firebase] messaging:messaging didReceiveRegistrationToken:fcmToken];
}
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    NSLog(@"APNs Unable to register for remote notifications: %@", error);
}
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    NSLog(@"APNs device token retrieved: %@", deviceToken);
    NSString *deviceTokenString = [[[[deviceToken description] 
    stringByReplacingOccurrencesOfString: @"<" withString: @""] 
    stringByReplacingOccurrencesOfString: @">" withString: @""] 
    stringByReplacingOccurrencesOfString: @" " withString: @""];
    //set value for SDK
    [[GameSDK sharedInstance] gameInfo].devicetoken = deviceTokenString;
    //tracking uninstall
    [[GameSDK AppsFlyer] trackingUninstallOnAF:deviceToken];
}
- (void)application:(UIApplication *)application 
        didReceiveRemoteNotification:(NSDictionary *) userInfo {
    NSLog(@"APNs full message. %@", userInfo);
}
- (void)application:(UIApplication *)application 
      didReceiveRemoteNotification:(NSDictionary *) userInfo
          fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    // Print full message.
    NSLog(@"APNs receive_message %@", userInfo);
    completionHandler(UIBackgroundFetchResultNewData);
}
// [START ios_10_message_handling]
// Receive displayed notifications for iOS 10 devices.
// Handle incoming notification messages while app is in the foreground.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center
       willPresentNotification:(UNNotification *)notification
         withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler API_AVAILABLE(ios(10.0)){
    NSDictionary *userInfo = notification.request.content.userInfo;
    // Print full message.
    [[GameSDK Firebase] showInAppMessage:userInfo];
    // Change this to your preferred presentation option
    completionHandler(UNNotificationPresentationOptionBadge);
}

// Handle notification messages after display notification is tapped by the user.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center
didReceiveNotificationResponse:(UNNotificationResponse *)response
         withCompletionHandler:(void(^)(void))completionHandler {
  NSDictionary *userInfo = response.notification.request.content.userInfo;
    [[GameSDK Firebase] showInAppMessage:userInfo];
  completionHandler();
}
// [END ios_10_message_handling]
```

# API description and usage
## Initialize GameSDK
```objectivec
#import "GameSDK.h"
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[GameSDK sharedInstance] initSdk];
    //...
}
```
## Initialize SDK delegate
```objectivec
//MainViewController.h
@interface MainViewController:UIViewController<UIActionSheetDelegate, SKProductsRequestDelegate, LoginDelegate, IAPDelegate> {
}
```
```objectivec
//MainViewController.m
#pragma Login Delegate
- (void)loginSuccess:(NSString *)userID andUserName:(NSString *)userName andAccessToken:(NSString *)access_token {
}
- (void)loginFail:(NSString *)message {
}
#pragma Logout Delegate
- (void) logoutSuccess{
}
#pragma IAP Delegate
- (void) IAPInitFailed:(NSString *)message andErrorCode:(NSString *)errorCode {
}
- (void) IAPPurchaseFailed:(NSString *)message andErrorCode:(NSString *)errorCode {
}
- (void) IAPCompleted:(NSString *)message{
}
```
## Show Login/Logout Interface
```objectivec
[[GameSDK sharedInstance] showSignInView:self andResultDelegate:self];
//showSignInView: use as main view controller
//andResultDelegate: use as Login Delegate
[[GameSDK sharedInstance] IDSignOut:self];
//use as Logout Delegate
```
## Delete Account API
```objectivec
[[GameSDK sharedInstance] deleteAcount:self andCallback:^(NSDictionary *response) {
    NSLog(@"response = %@", response);
}];
```

## Using IAP
*** appleSecret default is empty (ex: @""), this will change when we send the request to you
  
```objectivec
IAPDataRequest *iapData = [[IAPDataRequest alloc] 
          initWithData:_userName 
          andOrderId:orderID 
          andOrderInfo:orderInfo 
          andServerID:server 
          andAmount:amount 
          andAppleProductID:productID 
          andAppleShareSecrect:appleSecret 
          andRoleID:character 
          andExtraInfo:extraInfo];
[[GameSDK sharedInstance] showIAP:(IAPDataRequest *)iapData andMainView:self andIAPDelegate:self];
//andMainView: use as main view controller
//andIAPDelegate: use as IAP Delegate
```

# API Tracking Events
1. Tracking AppOpen On GameSDK
```objectivec
[[GameSDK ServerIdTracking] idAppTrackingOpen:serverID roleID:roleID roleName:roleName];
```
2. Tracking with Appsflyer
```objectivec
//Custom event:Custom event parameters will be provided separately
[[GameSDK AppsFlyer] trackingEventOnAF:@"eventName" withValues:(NSDictionary *)values];
//tracking start trial
[[GameSDK AppsFlyer] trackingStartTrialEventOnAF];
//tracking Turial Completion
[[GameSDK AppsFlyer] trackingTurialCompletedEventOnAF];
//tracking Spent Credit
[[GameSDK AppsFlyer] trackingSpentCreditEventOnAF:@"gamer_level"];
//tracking Level Achieved
[[GameSDK AppsFlyer] trackingLevelArchiveEventOnAF:@"gamer_level"];
//tracking Achievement unlocked
[[GameSDK AppsFlyer] trackingArchiveUnlockEventOnAF:@"gamer_level"];
```
3. Tracking with Firebase
```objectivec
//tracking start trial
[[GameSDK Firebase] trackingEventOnFirebase:@"eventName" parameters:@{@"eventEventLogKey":@"eventEventLogValue"}];
[[GameSDK Firebase] trackingScreenOnFirebase:@"screenName" screenClass:@"screenClass"];
[[GameSDK Firebase] setUserPropertiesOnFirebase:@"userValue" forName:@"usernameName"];
//    subscribe
[[GameSDK Firebase] FirebaseSubscribeToTopic:@"topicName"];
[[GameSDK Firebase] FirebaseUnSubscribeToTopic:@"topicName"];
```
  
By using the GameSDK for iOS you agree to these terms.
