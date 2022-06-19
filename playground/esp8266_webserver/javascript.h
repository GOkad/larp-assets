/*
* Get webpage JavaScript
* @return String javaScript - webpage JS functionality
*/
String getJavaScript ( ) {
  String javaScript = "<script type='text/javascript'>";
  // Set IPs as const
  javaScript += "const AP_IP='";
  javaScript += WiFi.softAPIP().toString();
  javaScript += "';";
  javaScript += "const NC_IP='";
  javaScript += WiFi.localIP().toString();
  javaScript += "';";
  javaScript += "function fetchData ( endpoint, data ) { ";
  javaScript += "fetch(`${endpoint}`).then( response => response.json() ).then(data => { ";
  javaScript += "console.log(data); ";
  javaScript += "document.querySelector('#test').innerHTML = data.string; });";
  javaScript += "console.log(`ap_ip: ${AP_IP} | nc_ip: ${NC_IP} | ${endpoint} | ${data}`); ";
  javaScript += " }";
  javaScript += "console.log('"+PROJECT_NAME+"')";

  javaScript += "</script>";
  return javaScript;
}
