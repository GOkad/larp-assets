/*
* Generate JSON response for API calls
* @return String jsonString - Stringified JSON object
*/
String buildJSONResponse ( String customString ) {
  String jsonString = "{";
  jsonString += "\"string\":\"";
  jsonString += customString;
  jsonString += "\",";
  jsonString += "\"rand\":";
  jsonString += random(300);
  jsonString += "}";
  return jsonString;
}