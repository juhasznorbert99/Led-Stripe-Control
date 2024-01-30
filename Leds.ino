
#define BLYNK_PRINT Serial
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LED_PIN 8
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define NUM_LEDS 60
#define BRIGHTNESS 100
#define FRAMES_PER_SECOND 60
#define GRAVITY -10
#define h0 1
#define NUM_BALLS 7
#define COOLING  55
#define SPARKING 120

float h[NUM_BALLS] ;
float vImpact0 = sqrt( -2 * GRAVITY * h0 );
float vImpact[NUM_BALLS] ;
float tCycle[NUM_BALLS] ;
int   pos[NUM_BALLS] ;
long  tLast[NUM_BALLS] ;
float COR[NUM_BALLS] ;
CRGB leds[NUM_LEDS];
bool gReverseDirection = false;

char auth[] = "ZJhFolfB1WH5PWT9Gv-UipS-eVhtQZeP";
char ssid[] = "Mami";
char pass[] = "norbinorbi";


int zebraButton;
BLYNK_WRITE(V0)
{
  zebraButton = param.asInt();
}

int bouncingButton;
BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  bouncingButton = param.asInt(); 
 
}
int fireButton;
BLYNK_WRITE(V2) //Button Widget is writing to pin V2
{
  fireButton = param.asInt(); 
}

int red;
int green;
int blue;
BLYNK_WRITE(V3)
{
  red = param[0].asInt();
  green = param[1].asInt();
  blue = param[2].asInt();
}

int prideButton;
BLYNK_WRITE(V4)
{
  prideButton = param.asInt();
}

int confettiButton;
BLYNK_WRITE(V5)
{
  confettiButton = param.asInt();
}


int sinelonButton;
BLYNK_WRITE(V6)
{
  sinelonButton = param.asInt();
}

int juggleButton;
BLYNK_WRITE(V7)
{
  juggleButton = param.asInt();
}

int bpmButton;
BLYNK_WRITE(V8)
{
  bpmButton = param.asInt();
}

void fire()
{
    static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void bouncingBall(){
  for (int i = 0 ; i < NUM_BALLS ; i++) {
    tCycle[i] =  millis() - tLast[i] ;
    h[i] = 0.5 * GRAVITY * pow( tCycle[i]/1000 , 2.0 ) + vImpact[i] * tCycle[i]/1000;

    if ( h[i] < 0 ) {                      
      h[i] = 0;
      vImpact[i] = COR[i] * vImpact[i] ;
      tLast[i] = millis();

      if ( vImpact[i] < 0.01 ) vImpact[i] = vImpact0;
    }
    pos[i] = round( h[i] * (NUM_LEDS - 1) / h0);
  }
  for (int i = 0 ; i < NUM_BALLS ; i++) leds[pos[i]] = CHSV( uint8_t (i * 40) , 255, 255);
  FastLED.setBrightness( 255 );
  FastLED.show();
  for (int i = 0 ; i < NUM_BALLS ; i++) {
   leds[pos[i]] = CRGB::Black;
  }
    
}

uint8_t gHue = 0;
void confetti() 
{
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);
  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    nblend( leds[pixelnumber], newcolor, 64);
  }
  FastLED.show();
}


void bpm()
{
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++)
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void sinelon()
{
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) 
  {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND);
}


void zebra()
{
  for(int i = 0; i< NUM_LEDS; i++)
  {
    leds[i] = CRGB(red,green,blue);
  }
  FastLED.setBrightness( 255 );
  FastLED.show();
}

void black()
{

  for(int i = 0; i< NUM_LEDS; i++)
  {
    leds[i] =  CRGB::Black;
  }
  
  FastLED.setBrightness( 255 );
  FastLED.show();
}

void redLight()
{

  for(int i = 0; i< NUM_LEDS; i++)
  {
    leds[i] =  CRGB::Red;
  }
  
  FastLED.setBrightness( 255 );
  FastLED.show();
}
int lastSoundValue;
int soundValue;
long lastNoiseTime = 0;
long currentNoiseTime = 0;
long lastLightChange = 0;


int relayStatus = HIGH;

void setup()
{
  // Debug console
   pinMode(D0, INPUT);
  
   Serial.begin(115200);
   FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness( BRIGHTNESS );
   Blynk.begin(auth, ssid, pass);
   for (int i = 0 ; i < NUM_BALLS ; i++) {
      tLast[i] = millis();
      h[i] = h0;
      pos[i] = 0;
      vImpact[i] = vImpact0;
      tCycle[i] = 0;
      COR[i] = 0.90 - float(i)/pow(NUM_BALLS,2); 
    }
    FastLED.clear();
  
}
void loop()
{
  Blynk.run();

  if (relayStatus == HIGH)
    redLight();
  soundValue = digitalRead(D0);
  currentNoiseTime = millis();
    if (soundValue == 1) { // if there is currently a noise

    if (
      (currentNoiseTime > lastNoiseTime + 200) && // to debounce a sound occurring in more than a loop cycle as a single noise
      (lastSoundValue == 0) &&  // if it was silent before
      (currentNoiseTime < lastNoiseTime + 800) && // if current clap is less than 0.8 seconds after the first clap
      (currentNoiseTime > lastLightChange + 1000) // to avoid taking a third clap as part of a pattern
    ) {
      
       relayStatus = !relayStatus;
      
      lastLightChange = currentNoiseTime;
     }

     lastNoiseTime = currentNoiseTime;
  }

  lastSoundValue = soundValue;


  
  if(bouncingButton == 1)
  {
      bouncingBall();
  }
  else
      if(bouncingButton == 0)
        black();




  if(fireButton == 1)
  {
      fire();
  }
  else
      if(fireButton == 0)
        black();

  if( zebraButton == 1)
  {
    zebra();
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);
  }else
  {
    if(zebraButton == 0)
        black();
  }
  
  if( prideButton == 1)
  {
    pride();
  }else
  {
    if(prideButton == 0)
        black();
  }  
  if( confettiButton == 1)
  {
    confetti();
  }else
  {
    if(confettiButton == 0)
        black();
  } 

  if( juggleButton == 1)
  {
    juggle();
  }else
  {
    if(juggleButton == 0)
        black();
  } 

  
  if( sinelonButton == 1)
  {
    sinelon();
  }else
  {
    if(sinelonButton == 0)
        black();
  } 

  
  if( bpmButton == 1)
  {
    bpm();
  }else
  {
    if(bpmButton == 0)
        black();
  } 
}
