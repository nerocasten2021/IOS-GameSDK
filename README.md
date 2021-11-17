# IOS GameSDK

[![Platforms](https://img.shields.io/cocoapods/p/FBSDKCoreKit.svg)]()

### This guide shows you how to integrate your iOS app using the GameSDK for iOS. The GameSDK for iOS consists of the following component:
  - The GameSDK Core
  - GoogleSigin SDK 
  - Firebase SDK
  - Facebook SDK
  - AppsFlyer SDK (Custom event parameters will be provided via email )
### FEATURES:
  - Login: Authenticate people with their my server ID, Google and Facebook credentials.
  - Payment IAP: Pay to buy products from in-app
  - Track Events: Track events with third parties including Appsflyer and Firebase tracking
  - You will need some included keys:Client ID, Facebook App ID, FacebookClient Token and GoogleService-Info.plist file

# Try It Out

* Download GameSDK latest
* GoogleService-Info.plist: send via mail
* Download Third party framework (FacebooSDK, FirebaseSDK, AppsflyerSDK)
* Install the following: App Tracking Transparency framework only available starting from Xcode 12 or later-The SDK supports iOS10+

# Integrate

- GameSDK latest version
- Embed Third party framework
- Some other libraries: 
  - AuthenticationServices.framework
  - MediaPlayer.framework
  - MobileCoreServices.framework
  - SystemConfiguration.framework
  - MessageUI.framework
- Embed FacebookSDK framework (FBSDK*) with embed content is **Embed & Sign**
