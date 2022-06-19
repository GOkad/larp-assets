const String HTML_DATA_REPLACE = "[BODY_CONTENT]";

/*
* Get webpage html body content
* @return String body - webpage body content
*/
String getHTML ( ) {
  String body = "";
  body += "<body>";
  body += "<h1>"+PROJECT_NAME+"</h1>";
  body += "<p id='test'>Response data: [null]</p>";
  body += "<button ontouchstart='fetchData( `/api/led-on` )' ontouchend='fetchData( `/api/led-off` )'> LED on </button> <br>";
  body += "<button onclick='fetchData( `/api/led-off` )'> Toggle button </button> <br>";
  body += HTML_DATA_REPLACE;
  body += "</body>";
  return body;
}
