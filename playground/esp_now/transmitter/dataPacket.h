/*
* Data Packet types enum
*/
enum data_packet_types {
	PROP = 0,
	DANGER,
	STATION,
};

const int MIN_DISTANCE = 200;
const int MAX_DISTANCE = 500;

const int MIN_THREAT = 0;
const int MID_THREAT = 50;
const int MAX_THREAT = 100;

const String data_type_message[] = {
  "Loot Box / Prop",
  "Something dangerous",
  "Work/Safe Station"
};

struct __attribute__((packed)) dataPacket {
  int type;
  int activeDistance;
  int threatLevel;
};