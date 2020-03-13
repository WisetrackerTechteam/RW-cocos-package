### <a id="INSTALL"></a> Installation

##### <a id="DOWNLOAD"></a> a) SDK Download
Android 프로젝트 app/build.gradle 파일 dependencies 불록에 의존성 추가

```gradle
dependencies {
    implementation fileTree(dir: 'libs', include: ['*.jar']) 
    ....
    implementation 'com.sdk.wisetracker.base:base_module_test:0.0.73' // BASE
    implementation 'com.sdk.wisetracker.new_dot:new_dot_module_test:0.0.73'   // DOT
    implementation 'com.sdk.wisetracker.dox:dox_module_test:0.0.73'   // DOX
}
```

##### <a id="APPKEY"></a> b) dotAuthorizationKey 등록
Android 프로젝트의 app/res/values/strings.xml 파일에 제공받은 App Analytics Key 정보를 추가
```xml
<string-array name="dotAuthorizationKey">
    <item name="usdMode">1</item> // 1. DOT/DOX 2. DOT
    <item name="domain">http://collector.naver.wisetracker.co.kr</item> // DOT END POINT
    <item name="domain_x">http://collector.naver.wisetracker.co.kr</item> // DOX END POINT
    <item name="serviceNumber">103</item>
    <item name="expireDate">14</item>
    <item name="isDebug">false</item>
    <item name="isInstallRetention">true</item>
    <item name="isFingerPrint">true</item>
    <item name="accessToken">access_token_string</item>
</string-array>
```

##### <a id="HTTP"></a> c) Http 통신 허용 설정
프로젝트의 **Target API 28** 이상일 경우 Http 통신 허용을 설정해 주세요.

```xml
<!-- AndroidManifest.xml -->
<application
	android:icon="@mipmap/ic_launcher"
	android:label="@string/app_name"
	android:networkSecurityConfig="@xml/network_security_config"
	android:theme="@style/AppTheme">
```
	
```xml
<!-- app/res/xml/network_security_config.xml -->
<?xml version="1.0" encoding="utf-8"?>
<network-security-config>
    <domain-config cleartextTrafficPermitted="true">
        <domain includeSubdomains="true">collector.naver.wisetracker.co.kr</domain>
        <domain includeSubdomains="true">report.wisetracker.co.kr</domain>
    </domain-config>
</network-security-config>
```

##### <a id="INSTALL_REFERRER_FLAG"></a> d) 인스톨 레퍼러 활성화 여부 (필요시 사용)

```xml
<!-- 레퍼러 정보 직접 수신 할 경우에만 해당 코드 삽입 -->
<meta-data 
    android:name="disableDotReceiver"
    android:value="true" />
```

##### <a id="CUSTOM_KEY_LIST"></a> e) customKeyList 설정 (필요시 사용)
'#' 구분자 기준으로 왼쪽은 기본 사용되고 있는 키 값 오른쪽은 변경하고자 하는 키 값을 적용해주세요.

```xml
<!-- 예시는 디폴트 advtId 키 값을 advt_id 값으로 변경하는 설정 -->
<string-array name="customKeyList">
  <item name="custom_key_value1">advtId#advt_id</item>
</string-array>
```
