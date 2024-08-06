#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED_RED 11
#define LED_GREEN 12

int duration;
int distance;
const int numDistanceLimits = 3;  // Number of distance limit values
int distanceLimits[numDistanceLimits] = {10, 20, 30};  // Array of distance limits, 30 is the limit, while 10 & 20 will be the data

void setup() 
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  calculateDistance();  // Call user-defined function to calculate distance
  
  // The array of distance limits and set LEDs based on distance
  for (int i = 0; i < numDistanceLimits; i++)
  {
    if (distance < distanceLimits[i]) {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      break;  // Exit the loop once a condition is met
    } else {
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
    }
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  delay(100);
}

// User-defined function to calculate distance
void calculateDistance() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);              
  distance = (duration * 0.0343) / 2;
}