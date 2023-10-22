/**
  * Most code taken from stepper motor video tutorial lesson.
  * https://www.youtube.com/watch?v=TQ7R2bY-MWU 
  * by Robojax
  * Modified and other parts written by Maika Hirata.
  */
const int pin1 = 10; // IN1
const int pin2 = 11; // IN2
const int pin3 = 12; // IN3
const int pin4 = 13; // IN4
const int switchCW = 2;
const int switchCCW = 3;

int pole1[] = {0, 0, 0, 0,  0, 1, 1, 1,  0};
int pole2[] = {0, 0, 0, 1,  1, 1, 0, 0,  0};
int pole3[] = {0, 1, 1, 1,  0, 0, 0, 0,  0};
int pole4[] = {1, 1, 0, 0,  0, 0, 0, 1,  0};

int poleStep = 0;
int directionStatus = 3; // stores direction status (1 = CCW, 2 = CW, 3 = stop)

void setup() {
  // put your setup code here, to run once:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  pinMode(switchCW, INPUT_PULLUP);
  pinMode(switchCCW, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(poleStep);
  if (digitalRead(switchCCW) == LOW) {
    directionStatus = 1;
  } else if (digitalRead(switchCW) == LOW) {
    directionStatus = 2;
  } else {
    directionStatus = 3;
  } // if

  if (directionStatus == 1) {
    poleStep++;
    driveStepper(poleStep);
  } else if (directionStatus == 2) {
    poleStep--;
    driveStepper(poleStep);
  } else {
    driveStepper(8);
  } // if

  if (poleStep > 7) {
    poleStep = 0;
  } // if

  if (poleStep < 0) {
    poleStep = 7;
  } // if

  delay(1); // necessary so motor has enough time to move from one step to next step
}

/**
  * Moves stepper motor in specified direction.
  * @param "c" integer representing the pol of motor
  *
  * www.Robojax.com code June 2019
  */
void driveStepper(int c) {
  digitalWrite(pin1, pole1[c]);
  digitalWrite(pin2, pole2[c]);
  digitalWrite(pin3, pole3[c]);
  digitalWrite(pin4, pole4[c]);
} // drivestepper