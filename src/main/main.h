#include <GSM.h>
//#include <LiquidCrystal.h>

// Other variables 
const byte rows=4;               // Number of rows of keypad
const byte columns=4;            // Number of columnss of keypad
boolean notConnected = true;     // GSM Connection state

/* ============================= PINES DE CONEXION ============================= */

// Pins used for the LEDs. Arduino MEGA GSM shield has pins 2,3,7 and 10 reserved.
const int pinLED_1 = 4;                     // LED green when the message is sent
const int pinLED_2 = 5;                     // LED green when the message is received by the receiver
const int pinLED_3 = 6;                     // LED blue when the message has been read by the receiver

// Pin used for the Buzzer
const int pinBuzzer = 8;

// Pins used for the Keypad
const byte Output[rows]={25,27,29,31};      // Array of pins used as output for rows of keypad
const byte Input[columns]={33,35,37,39};    // Array of pins used as input for columnss of keypad

// Pins used for the LCD
//const int lcdPin[6]={51,53,9,11,12,13};

/* ============================= TECLADO DE MEMBRANA ============================= */

byte h=0,v=0;                   // Variables used in for loops
const unsigned long period=50;  // Little period used to prevent error
unsigned long kdelay=0;         // Variable used in non-blocking delay 
char key = 'p';                 // Variable to control the key pressed
bool flag = false;              // Flag to add a new introduced digit to the complete password
String mobile_code = "4568";     // Code to unlock the program using the keypad

/* ============================= SMS ============================= */

// GSM library instances to send SMS and to access GSM service in the shield
GSM gsmAccess;
GSM_SMS sms;

char pin[] = "5056";                  // PIN number of the SIM Card of the GSM Shield we are using
char* file_data;
String msg_send = "";                 // Message to send through the serial port to the mobile number
String msg_recv = "";                 // Message to receive from the serial port from another phone number
String phoneNumber = "";              // Phone number of the receiver
String pN = "";


String sender_phoneNumber_str = "";
String receiver_phoneNumber_str = "";
char sender_phoneNumber[20];          // Variable used to store the number of the SENDER
char receiver_phoneNumber[20];        // Variable used to store the number of the RECEIVER
int8_t answer;

/* ============================= PANTALLA LCD ============================= */

// Initialize the library by providing the nuber of pins to it
//LiquidCrystal lcd(lcdPin[0], lcdPin[1], lcdPin[2], lcdPin[3], lcdPin[4], lcdPin[5]);

/* ============================= BUZZER ============================= */

double noteFreqArrSend[] = {
  43.066406,   86.132813,  129.199219,  172.265625,  215.332031,  258.398438,  301.464844,  344.531250,  387.597656,
 430.664063,  473.730469,  516.796875,  559.863281,  602.929688,  645.996094,  689.062500,  732.128906,  775.195313,
 818.261719,  861.328125,  904.394531,  947.460938,  990.527344, 1033.593750, 1076.660156, 1119.726563, 1162.792969,
1205.859375, 1248.925781, 1291.992188, 1335.058594, 1378.125000, 1421.191406, 1464.257813, 1507.324219, 1550.390625,
1593.457031, 1636.523438,
1679.589844, 
1722.656250,
1765.722656,
1808.789063,
1851.855469,
1894.921875,
1937.988281,
1981.054688,
2024.121094,
2067.187500,
2110.253906,
2153.320313,
2196.386719,
2239.453125,
2282.519531,
2325.585938,
2368.652344,
2411.718750,
2454.785156,
2497.851563,
2540.917969,
2583.984375,
2627.050781,
2670.117188,
2713.183594,
2756.250000,
2799.316406,
2842.382813,
2885.449219,
2928.515625,
2971.582031,
3014.648438,
3057.714844,
3100.781250,
3143.847656,
3186.914063,
3229.980469,
3273.046875,
3316.113281,
3359.179688,
3402.246094,
3445.312500,
3488.378906,
3531.445313,
3574.511719,
3617.578125,
3660.644531,
3703.710938,
3746.777344,
3789.843750,
3832.910156,
3875.976563,
3919.042969,
3962.109375,
4005.175781,
4048.242188,
4091.308594,
4134.375000,
4177.441406,
4220.507813,
4263.574219,
4306.640625,
4349.707031,
4392.773438,
4435.839844,
4478.906250,
4521.972656,
4565.039063,
4608.105469,
4651.171875,
4694.238281,
4737.304688,
4780.371094,
4823.437500,
4866.503906,
4909.570313,
4952.636719,
4995.703125,
5038.769531,
5081.835938,
5124.902344,
5167.968750,
5211.035156,
5254.101563,
5297.167969,
5340.234375,
5383.300781,
5426.367188,
5469.433594,
5512.500000,
5555.566406,
5598.632813,
5641.699219,
5684.765625,
5727.832031,
5770.898438,
5813.964844,
5857.031250,
5900.097656,
5943.164063,
5986.230469,
6029.296875,
6072.363281,
6115.429688,
6158.496094,
6201.562500,
6244.628906,
6287.695313,
6330.761719,
6373.828125,
6416.894531,
6459.960938,
6503.027344,
6546.093750,
6589.160156,
6632.226563,
6675.292969,
6718.359375,
6761.425781,
6804.492188,
6847.558594,
6890.625000,
6933.691406,
6976.757813,
7019.824219,
7062.890625,
7105.957031,
7149.023438,
7192.089844,
7235.156250,
7278.222656,
7321.289063,
7364.355469,
7407.421875,
7450.488281,
7493.554688,
7536.621094,
7579.687500,
7622.753906,
7665.820313,
7708.886719,
7751.953125,
7795.019531,
7838.085938,
7881.152344,
7924.218750,
7967.285156,
8010.351563,
8053.417969,
8096.484375,
8139.550781,
8182.617188,
8225.683594,
8268.750000,
8311.816406,
8354.882813,
8397.949219,
8441.015625,
8484.082031,
8527.148438,
8570.214844,
8613.281250,
8656.347656,
8699.414063,
8742.480469,
8785.546875,
8828.613281,
8871.679688,
8914.746094,
8957.812500,
9000.878906,
9043.945313,
9087.011719,
9130.078125,
9173.144531,
9216.210938,
9259.277344,
9302.343750,
9345.410156,
9388.476563,
9431.542969,
9474.609375,
9517.675781,
9560.742188,
9603.808594,
9646.875000,
9689.941406,
9733.007813,
9776.074219,
9819.140625,
9862.207031,
9905.273438,
9948.339844,
9991.406250,
10034.472656,
10077.539063,
10120.605469,
10163.671875,
10206.738281,
10249.804688,
10292.871094,
10335.937500,
10379.003906,
10422.070313,
10465.136719,
10508.203125,
10551.269531,
10594.335938,
10637.402344,
10680.468750,
10723.535156,
10766.601563,
10809.667969,
10852.734375,
10895.800781,
10938.867188,
10981.933594,
11025.000000,
11068.066406,
11111.132813,
11154.199219,
11197.265625,
11240.332031,
11283.398438,
11326.464844,
11369.531250,
11412.597656,
11455.664063,
11498.730469,
11541.796875,
11584.863281,
11627.929688,
11670.996094,
11714.062500,
11757.128906,
11800.195313,
11843.261719,
11886.328125,
11929.394531,
11972.460938,
12015.527344,
12058.593750,
12101.660156,
12144.726563,
12187.792969,
12230.859375,
12273.925781,
12316.992188,
12360.058594,
12403.125000,
12446.191406,
12489.257813,
12532.324219,
12575.390625,
12618.457031,
12661.523438,
12704.589844,
12747.656250,
12790.722656,
12833.789063,
12876.855469,
12919.921875,
12962.988281,
13006.054688,
13049.121094,
13092.187500,
13135.253906,
13178.320313,
13221.386719,
13264.453125,
13307.519531,
13350.585938,
13393.652344,
13436.718750,
13479.785156,
13522.851563,
13565.917969,
13608.984375,
13652.050781,
13695.117188,
13738.183594,
13781.250000,
13824.316406,
13867.382813,
13910.449219,
13953.515625,
13996.582031,
14039.648438,
14082.714844,
14125.781250,
14168.847656,
14211.914063,
14254.980469,
14298.046875,
14341.113281,
14384.179688,
14427.246094,
14470.312500,
14513.378906,
14556.445313,
14599.511719,
14642.578125,
14685.644531,
14728.710938,
14771.777344,
14814.843750,
14857.910156,
14900.976563,
14944.042969,
14987.109375,
15030.175781,
15073.242188,
15116.308594,
15159.375000,
15202.441406,
15245.507813,
15288.574219,
15331.640625,
15374.707031,
15417.773438,
15460.839844,
15503.906250,
15546.972656,
15590.039063,
15633.105469,
15676.171875,
15719.238281,
15762.304688,
15805.371094,
15848.437500,
15891.503906,
15934.570313,
15977.636719,
16020.703125,
16063.769531,
16106.835938,
16149.902344,
16192.968750,
16236.035156,
16279.101563,
16322.167969,
16365.234375,
16408.300781,
16451.367188,
16494.433594,
16537.500000,
16580.566406,
16623.632813,
16666.699219,
16709.765625,
16752.832031,
16795.898438,
16838.964844,
16882.031250,
16925.097656,
16968.164063,
17011.230469,
17054.296875,
17097.363281,
17140.429688,
17183.496094,
17226.562500,
17269.628906,
17312.695313,
17355.761719,
17398.828125,
17441.894531,
17484.960938,
17528.027344,
17571.093750,
17614.160156,
17657.226563,
17700.292969,
17743.359375,
17786.425781,
17829.492188,
17872.558594,
17915.625000,
17958.691406,
18001.757813,
18044.824219,
18087.890625,
18130.957031,
18174.023438,
18217.089844,
18260.156250,
18303.222656,
18346.289063,
18389.355469,
18432.421875,
18475.488281,
18518.554688,
18561.621094,
18604.687500,
18647.753906,
18690.820313,
18733.886719,
18776.953125,
18820.019531,
18863.085938,
18906.152344,
18949.218750,
18992.285156,
19035.351563,
19078.417969,
19121.484375,
19164.550781,
19207.617188,
19250.683594,
19293.750000,
19336.816406,
19379.882813,
19422.949219,
19466.015625,
19509.082031,
19552.148438,
19595.214844,
19638.281250,
19681.347656,
19724.414063,
19767.480469,
19810.546875,
19853.613281,
19896.679688,
19939.746094,
19982.812500,
20025.878906,
20068.945313,
20112.011719,
20155.078125,
20198.144531,
20241.210938,
20284.277344,
20327.343750,
20370.410156,
20413.476563,
20456.542969,
20499.609375,
20542.675781,
20585.742188,
20628.808594,
20671.875000,
20714.941406,
20758.007813,
20801.074219,
20844.140625,
20887.207031,
20930.273438,
20973.339844,
21016.406250,
21059.472656,
21102.539063,
21145.605469,
21188.671875,
21231.738281,
21274.804688,
21317.871094,
21360.937500,
21404.003906,
21447.070313,
21490.136719,
21533.203125,
21576.269531,
21619.335938,
21662.402344,
21705.468750,
21748.535156,
21791.601563,
21834.667969,
21877.734375,
21920.800781,
21963.867188,
22006.933594};

double noteFreqArrRecv[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};

int noteDurationArrSend[] = {
  500
};

int noteDurationArrRecv[] = {
  250
};

int countTonesSend = 511;
int countTonesRecv = 0;
