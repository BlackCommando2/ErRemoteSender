//logori_pick_ps4_sender
#include <PS4-ActionMonitor.h>
String datastring;
int basex, basey, baser;
int baselX, baselY, baserX, baserY;
long currentTime = 0;
static long previousTime;
bool rumble = false, done = true, opt = false, init_ = false, zeroCheck = false, pressed = false;
bool autoDown = false, autoCompute = false, autoBase = false;
bool setAllAnalog = false;
void setup()
{
  Serial.begin(115200);
  Serial2.begin(921600);
  initPS4("11:11:11:11:11:11");
  //  initPS4("22:22:22:22:22:22");
  getAllAnalog(setAllAnalog);
  //Attaching function with buttons
  square->attachPress(sqaurePressed);
  square->attachRelease(sqaureReleased);

  circle->attachPress(circlePressed);
  circle->attachRelease(circleReleased);

  triangle->attachPress(trianglePressed);
  triangle->attachRelease(triangleReleased);

  cross->attachPress(crossPressed);
  cross->attachRelease(crossReleased);

  up->attachPress(upPressed);
  up->attachRelease(upReleased);

  down->attachPress(downPressed);
  down->attachRelease(downReleased);

  left->attachPress(leftPressed);
  left->attachRelease(leftReleased);

  right->attachPress(rightPressed);
  right->attachRelease(rightReleased);

  l1->attachPress(l1Pressed);
  l1->attachRelease(l1Released);

  r1->attachPress(r1Pressed);
  r1->attachRelease(r1Released);


  rJoystick->attachAnalogX(rightjoystickX);
  rJoystick->attachAnalogY(rightjoystickY);

  share->attachPress(sharePressed);
  share->attachRelease(shareReleased);

  options->attachPress(optionPressed);
  options->attachRelease(optionReleased);

  psButton->attachPress(psPressed);
  psButton->attachRelease(psReleased);

  touchpad->attachPress(touchpadPressed);
  touchpad->attachRelease(touchpadReleased);

  leftJoystick->attachAllData(base);
  //  allAnalog->attachAllAnalogData(directionalBase);
}
int lx, ly, rightX, rightY;
void loop()
{
  //  currentTime=millis();
  //  if(zeroCheck)
  //  {
  //    Serial2.print("0,0,0,\n");
  //    if(currentTime-previousTime>200)
  //    {
  //      zeroCheck=false;
  //      previousTime=currentTime;
  //    }
  //  }
  //Serial.println(PS4.Battery());
}
void rightjoystickX(int v)
{
  rightX = v;
  rightX = map(rightX, 0, 125, 0, 255);
  if (abs(rightX) >= abs(rightY))
  {
    datastring = String(rightX) + "," + "0" + "," + "0" + "," + "\n";
    Serial2.print(datastring);
  }
  else if (abs(rightX) < abs(rightY))
  {
    datastring = "0," + String(rightY) + ",0," + "\n";
    Serial2.print(datastring);
  }
  //  Serial.println("RightJoystick="+String(rightX)+","+String(rightY));
  Serial.println(datastring);
}
void rightjoystickY(int v)
{
  rightY =  v;
  rightY = map(rightY, 0, 125, 0, 255);
  if (abs(rightX) >= abs(rightY))
  {
    datastring = String(rightX) + "," + "0" + "," + "0" + "," + "\n";
    Serial2.print(datastring);
  }
  else if (abs(rightX) < abs(rightY))
  {
    datastring = "0," + String(rightY) + ",0," + "\n";
    Serial2.print(datastring);
  }
  //  Serial.println("RightJoystick="+String(rightX)+","+String(rightY));
  Serial.println(datastring);
}
void l1Pressed()
{
  Serial2.print("lpush\n");
  Serial.print("l1 Pressed\n");
}
void l1Released()
{
  Serial.print("l1 Released\n");
}

void r1Pressed()
{
  //  Serial2.print("plus\n");
  //  if (!autoBase)
  //  {
  //    Serial2.print("automode\n");
  //    autoCompute = false;
  //    Serial.println("autoMode");
  //  }
  //  else if (autoBase)
  //  {
  //    Serial2.print("aC\n");
  //    PS4.setRumble(0, 200);
  //    PS4.setLed(255, 0, 0);
  //    PS4.sendToController();
  //    autoCompute = true;
  //    Serial.println("autoComputeOn");
  //  }
  Serial2.print("bpush\n");
  Serial.print("r1 Pressed\n");
}
void r1Released()
{
  //    Serial2.println("r1 Released\n");
  Serial.println("r1 Released");
}

void crossPressed()
{
  Serial2.print("cross\n");
  //Serial.print("crossPressed\n");
}
void crossReleased()
{
  if (opt)
  {
    Serial2.print("rcross\n");
  }
  Serial.print("crossReleased\n");
}

void circlePressed()
{
  Serial2.print("circle\n");
  Serial.print("circlePressed\n");
}
void circleReleased()
{
  if (opt)
  {
    Serial2.print("rcircle\n");
  }
  Serial.print("circlePressed\n");
}

void trianglePressed()
{
  Serial2.print("triangle\n");
  //  Serial.print("trianglePressed\n");
}
void triangleReleased()
{
  if (opt)
  {
    Serial2.print("rtriangle\n");
  }
  Serial.print("triangleReleased\n");
}

void sqaurePressed()
{
  Serial2.print("square\n");
  //  Serial.print("sqaure pressed\n");
}
void sqaureReleased()
{
  if (opt)
  {
    Serial2.print("rsquare\n");
  }
  Serial.print("sqaure Released\n");
}

void upPressed()
{
  Serial2.print("u\n");
  Serial.print("up Pressed\n");
  pressed = true;
}
void upReleased()
{
  Serial2.print("rel\n");
  Serial.print("up Released\n");
  pressed = false;
}

void downPressed()
{
  Serial2.print("d\n");
  Serial.print("down Pressed\n");
  pressed = true;
  autoBase = true;
}
void downReleased()
{
  if (!autoCompute)
  {
    Serial2.print("rel\n");
    Serial.print("down Released\n");
    //    Serial.println("downStop");
  }

  if (autoCompute)
  {
    Serial2.print("aR\n");
    Serial.println("autoComputeOff");
    autoCompute = false;
    PS4.setRumble(0, 100);
    PS4.setLed(0, 255, 0);
    PS4.sendToController();
  }
  pressed = false;
  autoBase = false;
}

void rightPressed()
{
  //  Serial2.print("right pressed\n");
  Serial2.print("i\n");
  //  Serial.print("resetted\n");
  pressed = true;
  autoBase = true;
}
void rightReleased()
{
  if (autoCompute)
  {
    Serial2.print("aR\n");
    Serial.println("autoComputeOff");
    autoCompute = false;
    PS4.setRumble(0, 100);
    PS4.setLed(0, 255, 0);
    PS4.sendToController();
  }
  else if (!autoCompute)
  {
    Serial2.print("rel\n");
  }
  Serial.print("rightReleased\n");
  //Serial2.print("right Released\n");
  pressed = false;
  autoBase = false;
}

void leftPressed()
{
  Serial2.print("l\n");
  //  Serial2.print("rotate\n");
  Serial.print("left Pressed\n");
  pressed = true;
}
void leftReleased()
{
  Serial2.print("rel\n");
  //Serial2.print("released\n");
  Serial.print("left Released\n");
  pressed = false;
}

void sharePressed()
{
  Serial2.print("share\n");
  Serial.print("share Pressed\n");
}
void shareReleased()
{
  Serial.print("share Released\n");
}

void optionPressed()
{
  //  Serial2.print("resetted\n");
  Serial2.print("option\n");
  if (!opt)
  {
    Serial.println("option true");
    opt = true;
    PS4.setLed(0, 255, 0);
    PS4.sendToController();
  }
  else if (opt)
  {
    Serial.println("option false");
    opt = false;
    if (rumble)
    {
      PS4.setRumble(0, 150);
      PS4.setLed(255, 0, 150);
      PS4.sendToController();
    }
    else if (!rumble)
    {
      PS4.setRumble(0, 0);
      PS4.setLed(255, 150, 0);
      PS4.sendToController();
    }
  }
  Serial.print("option pressed\n");
}
void optionReleased()
{
  Serial.print("option Released\n");
}

void psPressed()
{
  Serial2.print("ps\n");
  if (!rumble)
  {
    rumble = true;
    PS4.setRumble(0, 150);
    PS4.setLed(255, 0, 150);
    PS4.sendToController();
  }
  else if (rumble)
  {
    rumble = false;
    PS4.setRumble(0, 0);
    PS4.setLed(255, 150, 0);
    PS4.sendToController();
  }
  //  if (rumble && !done)
  //  {
  //    done = true;
  //    rumble = false;
  //    PS4.setRumble(0, 0);
  //    PS4.setLed(255, 0, 150);
  //    PS4.sendToController();
  //    delay(10);
  //  }
  //  else if (!rumble && done)
  //  {
  //    rumble = false;
  //    done = false;
  //    PS4.setRumble(0, 150);
  //    PS4.setLed(255, 150, 0);
  //    PS4.sendToController();
  //    delay(10);
  //  }
  //  Serial.print("ps\n");
}
void psReleased()
{
  Serial.print("ps Released\n");
  //  if (!rumble && !done)
  //  {
  //    rumble = true;
  //  }
}

void touchpadPressed()
{
  Serial2.print("touch\n");
  Serial.print("touchpad pressed\n");
}
void touchpadReleased()
{
  Serial.print("touchpad Released\n");
}
void base(int x, int y, int r)
{
  basex = x;
  basey = y;
  baser = r;
  datastring = String(basex) + "," + String(basey) + "," + String(baser) + "," + "\n";
  Serial2.print(datastring);
//  Serial.println(datastring);
  //  Serial2.print(JSON.stringify(baseData)+"\n");

  //Serial.println("X=" + String(x) + " ,Y=" + String(y) + " ,R=" + String(r));
  //  Serial.println(JSON.stringify(baseData));
}

void directionalBase(int lX, int lY, int rX, int rY, int r)
{
  baselX = lX;
  baselY = lY;
  baserX = rX;
  baserX = rX;
  baser = r;
  datastring = String(baselX) + "," + String(baselY) + "," + String(baserX) + "," + String(baserY) + "," + String(baser) + "," + "\n";
//  Serial.println("lX: " + String(lX) + " lY: " + String(lY) + " rX: " + String(rX) + " rY: " + String(rY) + " , " + String(r));
}
