//
//  GameInfo.h
//  GameSDK
//
//  Created by Nero-Macbook on 11/2/21.
//
#import <Foundation/Foundation.h>

@interface GameInfo : NSObject

+ (GameInfo *) sharedInstance;

//initialze key
//status
@property (nonatomic, assign) BOOL      isReady;
@property (nonatomic, assign) BOOL      isLoading;
@property (nonatomic, strong) NSString *isCheckShowloginView;
@property (nonatomic, strong) NSString *loadServerConfig;
@property (nonatomic, assign) BOOL      isallownoti;
@property (nonatomic, assign) BOOL      install;
@property (nonatomic, assign) BOOL      isEnableBiometric;

//required key
@property (nonatomic,strong) NSString *gameid;
@property (nonatomic,strong) NSString *clientid;
@property (nonatomic,strong) NSString *secretkey;
@property (nonatomic,strong) NSString *serviceid;
@property (nonatomic,strong) NSString *servicekey;
@property (nonatomic, strong) NSString *gameBundleId;
@property (nonatomic,strong) NSString *googleID;
@property (nonatomic,strong) NSString *providerID;

//data
@property (nonatomic, strong) NSString *logID;
@property (nonatomic, strong) NSArray *productIDList;

//data runtime
@property (nonatomic, strong) NSString *accesstoken;
@property (nonatomic, strong) NSString *userID;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *userEmail;
@property (nonatomic, strong) NSString *userStatus;
@property (nonatomic, strong) NSString *devicetoken;
@property (nonatomic, strong) NSString *network;
//api
@property (nonatomic, strong) NSString *idApi;
@property (nonatomic, strong) NSString *pApi;

@property (nonatomic, assign) BOOL      isPlayNow;
@property (nonatomic, assign) BOOL      userSmsStatus;
@property (nonatomic, assign) BOOL      isProductReady;
@property (nonatomic, assign) BOOL      isSandbox;

//AppsFlyer
@property (nonatomic, strong) NSString *appflyerDevKey;
@property (nonatomic, strong) NSString *appflyerAppleID;

//for Ads
@property (nonatomic, strong) NSString *idads_app_key;
@property (nonatomic, strong) NSString *idads_app_signature;
@property (nonatomic, strong) NSString *environment;

//language
@property (nonatomic, strong) NSString *sdk_language;

- (GameInfo *) getGameInfo;
- (GameInfo *) getGameInfo:(void(^)(NSDictionary *))loadCallback;
- (GameInfo *)loadGameInfo:(void(^)(NSDictionary *))loadCallback;
- (void)updateAccessToken:(NSString *)accessToken;
- (void)clearConfigFile;
- (void)updateUserID:(NSString *)userid;
- (void)updateUserName:(NSString *)username;
- (void)updateAllowNoti:(BOOL) allow;
- (void)updateNetwork:(NSString *)network;
- (void)updatePlayNow:(BOOL)isPlaynow;
- (void)updateInstalled:(BOOL) install;
- (void)setLoggedInStatus:(BOOL)isLogged;
- (BOOL) isLoggedIn;

//set olde account
- (void) setOldAccount:(NSString *)oldAccount;
- (NSString *) getOldAccount;
- (void) enableBiometric;
- (void) disableBiometric;

@end
