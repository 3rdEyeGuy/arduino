#include <Servo.h>
servo myServo
int left= 180;
int right = 15;
int Mid = 90;

//ultrasonic init
int echo = A4;
int trig = A5;

int lDist = 0, rDist = 0, mDist = 0;

//Right wheel variable init
int spdR = 5;
int fR = 6;
int bR = 7;
//Left wheel variable init
int spdL = 11;
int fL = 9;
int bL = 8;

//wheel speed?
int SPD = 150;

void backward()
{
    digitalWrite(spdR, SPD);
    digitalWrite(spdL, SPD); 
    digitalWrite(fR,LOW);
    digitalWrite(bR,HIGH);
    digitalWrite(fL, LOW);
    digitalWrite(bL, HIGH);
}

void forward()
{
    digitalWrite(spdR, SPD);
    digitalWrite(spdL, SPD); 
    digitalWrite(fR, HIGH);
    digitalWrite(bR, LOW);
    digitalWrite(fL, HIGH);
    digitalWrite(bL, LOW);
}

void mLeft()
{
    digitalWrite(spdL, SPD);
    digitalWrite(spdR, SPD);
    digitalWrite(fL, HIGH);
    digitalWrite(bL, LOW);
    digitalWrite(fR, LOW);
    digitalWrite(bR, HIGH);
}

void mRight()
{
    digitalWrite(spdR, SPD);
    digitalWrite(spdL, SPD);
    digitalWrite(fR, HIGH);
    digitalWrite(bR, LOW);
    digitalWrite(fL, LOW);
    digitalWrite(bL, HIGH);
}

void stop()
{
    digitalWrite(spdR, LOW);
    digitalWrite(spdL, LOW);
}

int Distance()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    float cmDist = pulsin(echo, HIGH);
    cmDist = cmDist/58;
    return (int)cmDist;
}

void setup()
{
    myServo.attach(3);

    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);

    pinMode(spdR,OUTPUT);
    pinMode(fR,OUTPUT);
    pinMode(bR,OUTPUT);

    pinMode(spdL, OUTPUT);
    pinMode(fL,OUTPUT);
    pinMode(bL,OUTPUT);
    stop();
}


void loop()
{
    myServo.write(Mid);
    delay(500);
    mDist = Distance(); 
    
    if(mDist <= 20)
    {
        stop();         
        delay(500);
        myServo.write(left);
        delay(500);
        lDist = Distance();
        myServo.write(right);
        delay(500);
        rDist = Distance ();
        if(rDist > lDist)
        mRight();
        else if(lDist > rDist)
        mLeft();
        else if(rDist <= 20 || lDist <= 20)
        backward();
    }
    else forward();
}
