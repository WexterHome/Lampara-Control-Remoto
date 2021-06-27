
#include <FastLED.h>
#include <IRremote.h>


//////////CONFIGURACIÓN/////////////

//Códigos de los botones del mando IR
const long int KEY_ON_OFF = 0xFFA25D;
const long int KEY_LEFT = 0xFF02FD;
const long int KEY_RIGHT = 0xFFC23D;
const long int KEY_VOL_UP = 0xFF906F;
const long int KEY_VOL_DOWN = 0xFFA857;
const long int KEY_1 = 0xFF30CF;
const long int KEY_2 = 0xFF18E7;
const long int KEY_3 = 0xFF7A85;
const long int KEY_4 = 0xFF10EF;
const long int KEY_5 = 0xFF38C7;
const long int KEY_6 = 0xFF5AA5;
const long int KEY_7 = 0xFF42BD;
const long int KEY_8 = 0xFF4AB5;
const long int KEY_9 = 0xFF52AD;
const long int KEY_0 = 0xFF6897;



#define LED_PIN     9       //Pin de la matriz LED
#define SENSOR_IR_PIN  5    //Pin del sensor IR
#define NUM_LEDS    64      //Número de LEDs
#define BRIGHTNESS  200     //Brillo máximo
#define LED_TYPE    WS2812B //Tipo de LED
#define COLOR_ORDER GRB     //Orden de colores


/////////////PARA DESARROLLADORES/////////////


CRGB leds[NUM_LEDS];

IRrecv irrecv(SENSOR_IR_PIN);
decode_results results;


#define UPDATES_PER_SECOND 100




CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int Efecto;
bool Encendido = true;
uint8_t brightness = 255;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
  Serial.begin(9600);
  delay( 3000 );
  Serial.println(KEY_ON_OFF);
  irrecv.enableIRIn();
  // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  Efecto = 0;
}


void loop()
{

  LeerSensor();
  ChangePalette();
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  //FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{


  for ( int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void LeerSensor()
{
  while (!irrecv.isIdle());
  if (irrecv.decode(&results))
  {
    Serial.println(results.value,HEX);
    if(results.value == KEY_ON_OFF) Serial.print("Hola");
    switch (results.value)
    {
      case KEY_ON_OFF:
        if (Encendido == true) {
          brightness = 0;
          Encendido = false;
        }
        else {
          brightness = 255;
          Encendido = true;
        }
        break;
      case KEY_LEFT:
        if (brightness >= 50) {
          brightness = brightness - 40;
        }
        break;
      case KEY_VOL_DOWN:
        if (brightness >= 50) {
          brightness = brightness - 40;
        }
        break;
      case KEY_RIGHT:
        if (brightness <= 205) {
          brightness = brightness + 40;
        }
        break;
      case KEY_VOL_UP:
        if (brightness <= 205) {
          brightness = brightness + 40;
        }
        break;
      case KEY_1:
        Serial.print("EstoyAqui");
        Efecto = 1;
        break;
      case KEY_2:
        Efecto = 2;
        break;
      case KEY_3:
        Efecto = 3;
        break;
      case KEY_4:
        Efecto = 4;
        break;
      case KEY_5:
        Efecto = 5;
        break;
      case KEY_6:
        Efecto = 6;
        break;
      case KEY_7:
        Efecto = 7;
        break;
      case KEY_8:
        Efecto = 8;
        break;
      case KEY_9:
        Efecto = 9;
        break;
      case KEY_0:
        Efecto = 0;
        break;
    }
    delay(200);
    irrecv.resume();
  }
}
void ChangePalette()
{

  if ( Efecto ==  0)  {
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 1)  {
    currentPalette = OceanColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 2)  {
    currentPalette = RainbowStripeColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 3)  {
    SetupPurpleAndGreenPalette();
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 4)  {
    currentPalette = ForestColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 5)  {
    SetupPurpleAndPurpleStripedPalette();
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 6)  {
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 7)  {
    currentPalette = CloudColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 8)  {
    currentPalette = PartyColors_p;
    currentBlending = LINEARBLEND;
  }
  if ( Efecto == 9)  {
    currentPalette = LavaColors_p;
    currentBlending = LINEARBLEND;
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for ( int i = 0; i < 16; ++i) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupPurpleAndPurpleStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Purple);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Purple;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
