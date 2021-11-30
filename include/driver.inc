#if defined _driver
    #endinput
#endif
#define _driver

#include <a_samp>
#include <streamer>
#include <FCNPC>

#define MAX_PLAYERS 49

#define DRIVER_SKIN 30
#define DRIVER_SEAT 0

#define VEHICLE_COLOR 0
#define VEHICLE_ROT 0

#define NORMAL_TEXT_COLOR 0x00ff00ff
#define ERROR_TEXT_COLOR 0xff000000

#define INVALID_VEHICLE_ID 65535
#define VEHICLE_CREATE_ERROR 0

forward driver_create(playerid, modelid);
forward driver_goto(driverid, Float:x, Float:y, Float:z);
forward driver_destroy(driverid);

new Text3D:driverlabel[MAX_PLAYERS];

public driver_create(playerid, modelid){
  new driverid = FCNPC_Create("DRIVER");
  new Float:x, Float:y, Float:z;
  GetPlayerPos(playerid, x, y, z);
  x += 3;  y += 3;
  
  FCNPC_Spawn(driverid, DRIVER_SKIN, Float:x, Float:y, Float:z);
  new vehicleid = CreateVehicle(modelid, Float:x, Float:y, Float:z, VEHICLE_ROT, VEHICLE_COLOR, VEHICLE_COLOR, 0, 0);

  if(vehicleid == INVALID_VEHICLE_ID || vehicleid == VEHICLE_CREATE_ERROR){
    SendClientMessageToAll(ERROR_TEXT_COLOR, "Error - INVALID VEHICLE ID");
    FCNPC_Destroy(driverid);
    return 0;
  }

  FCNPC_PutInVehicle(driverid, vehicleid, DRIVER_SEAT);
  new drivertxt[32];
  format(drivertxt, sizeof(drivertxt), "Driver ID: %d", driverid);
  driverlabel[vehicleid] = Create3DTextLabel(drivertxt, NORMAL_TEXT_COLOR, 0, 0, 0, 40.0, 0, 0);
  Attach3DTextLabelToPlayer(driverlabel[vehicleid], driverid, 0, 0, 0);
  SendClientMessageToAll(NORMAL_TEXT_COLOR, "Driver spawn.");
  return 1;  
}

public driver_goto(driverid, Float:x, Float:y, Float:z){
  FCNPC_GoTo(driverid, x, y, z, 3, 1);
  return 1;
}

public driver_destroy(driverid){
  if(!FCNPC_IsValid(driverid)){
    SendClientMessageToAll(ERROR_TEXT_COLOR, "INVALID DRIVER ID");
    return 0;
  }
  new vehicleid = GetPlayerVehicleID(driverid);
  Delete3DTextLabel(driverlabel[vehicleid]);
  DestroyVehicle(vehicleid);
  FCNPC_Destroy(driverid);    
  SendClientMessageToAll(NORMAL_TEXT_COLOR, "Driver Destroyed.");
  return 1;  
}
