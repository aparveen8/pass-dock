1.  #include <Keypad.h>
2.  #include <EEPROM.h>
3.  #include <LiquidCrystal.h>
4.  #include <Servo.h>
5.  
6.  Servo myservo;
7.  int pos=0;
8.  const byte numRows= 4;          
9.  const byte numCols= 4;         
10. 
11. char keymap[numRows][numCols]= 
12. {
13. {'1', '2', '3', 'A'}, 
14. {'4', '5', '6', 'B'}, 
15. {'7', '8', '9', 'C'},
16. {'*', '0', '#', 'D'}
17. };
18. 
19. char keypressed;                 
20. char code[]= {'6','6','B','1'};
21. char code_buff1[sizeof(code)];
22. char code_buff2[sizeof(code)];  
23. 
24. short a=0,i=0,s=0,j=0;         
25. 
26. byte rowPins[numRows] = {0,1,2,3}; 
27. byte colPins[numCols]= {4,5,6,7}; 
28. int buzz=8;
29. LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
30. Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
31. 
32. void setup()
33. {
34. pinMode(buzz, OUTPUT);
35. myservo.attach(9);
36. lcd.begin (16,2);
37. lcd.setCursor(0,0);
38. lcd.print("PROJECT  MADE BY"); 
39. lcd.setCursor(1,1);   
40. lcd.print("AYESHA PARVEEN"); 
41. delay(2000);
42. lcd.clear();
43. lcd.setCursor(0,0);
44. lcd.print("Press * to_/door");
45. lcd.setCursor(0,1);
46. lcd.print("Press#tochg pass");
47. }
48. void loop()
49. {
50. keypressed = myKeypad.getKey();              
51. if(keypressed == '*'){                   
52. lcd.clear();
53. lcd.setCursor(1,0);
54. lcd.print("Enter passcode");
55. lcd.setCursor(2,1);
56. lcd.print("and press A");
57. delay(2000);
58. lcd.clear();
59. lcd.setCursor(2,0);
60. lcd.print("and press A");  
61. GetCode();                          
62. if(a==sizeof(code))          
63. OpenDoor();
64. else{
65. lcd.clear();               
66. lcd.print("Wrong passcode");
67. delay(1000);
68. lcd.clear4(); 
69. lcd.setCursor(4,0);
70. lcd.print("You are");
71. lcd.setCursor(2,1);
72. lcd.print("Unauthorized");                    
73. digitalWrite(buzz, HIGH);
74. }
75. delay(2000);
76. lcd.clear();
77. digitalWrite(buzz,LOW);
78. lcd.setCursor(0,0);
79. lcd.print("Press * to_/door");
80. lcd.setCursor(0,1);
81. lcd.print("Press#tochg pass");
82. }
83. 
84. if(keypressed == '#')
85. {                  
86. ChangeCode();
87. lcd.clear();
88. lcd.setCursor(0,0);
89. lcd.print("Press * to_/door");
90. lcd.setCursor(0,1);
91. lcd.print("Press#tochg pass");
92. }         
93. }
94. 
95. void GetCode(){                         //Getting code sequence
96.        i=0;                                       //All variables set to 0
97.        a=0; 
98.        j=0; 
99.                                      
100.  while(keypressed != 'A'){                                            //The user press A to confirm the code otherwise he can keep typing
101.  keypressed = myKeypad.getKey();                         
102.  if(keypressed != NO_KEY && keypressed != 'A' ){            
103.  lcd.setCursor(j,1);                                                       //This to write "*" on the LCD whenever a key is pressed it's position is controlled by j
104.  lcd.print("*");
105.  j++;
106.  if(keypressed == code[i]&& i<sizeof(code)){             //if the char typed is correct a and i increments to verify the next caracter
107.  a++;                                                                         //Now I think maybe I should have use only a or i ... too lazy to test it -_-'
108.  i++;
109.  }
110.  else
111.  a--;                                                      //if the character typed is wrong a decrements and cannot equal the size of code []
112.  }
113.  }
114.  keypressed = NO_KEY;
115.  }
116.  void ChangeCode(){                      //Change code sequence
117.  lcd.clear();
118.  lcd.print("Changing code");
119.  delay(1000);
120.  lcd.clear();
121.  lcd.print("Enter old code");
122.  lcd.setCursor(2,1);
123.  lcd.print("and press A");
124.  delay(2000);
125.  lcd.clear();
126.  lcd.setCursor(2,0);
127.  lcd.print("and press A");  
128.  GetCode();                                   //verify the old code first so you can change it
129.  if(a==sizeof(code)){                   //again verifying the a value
130.  lcd.clear();
131.  lcd.print("Changing code");
132.  GetNewCode1();                      //Get the new code
133.  GetNewCode2();                     //Get the new code again to confirm it
134.  s=0;
135.  for(i=0 ; i<sizeof(code) ; i++){                   //Compare codes in array 1 and array 2 from two previous functions
136.  if(code_buff1[i]==code_buff2[i])
137.  s++;                                                        //again this how we verifiy, increment s whenever codes are matching
138.  }
139.  if(s==sizeof(code))
140.  {             
141.  for(i=0 ; i<sizeof(code) ; i++){
142.  code[i]=code_buff2[i];         
143.  EEPROM.put(i, code[i]);
144.  }
145.  lcd.clear();
146.  lcd.print("Code Changed");
147.  digitalWrite(buzz, HIGH);
148.  delay(300); 
149.  digitalWrite(buzz, LOW);
150.  delay(300);
151.  delay(2000);
152.  }
153.  else{                         //In case the new codes aren't matching
154.  lcd.clear();
155.  lcd.print("Codes are not");
156.  lcd.setCursor(4,1);
157.  lcd.print("matching !!");
158.  digitalWrite(buzz, HIGH);
159.  delay(300); 
160.  digitalWrite(buzz, LOW);
161.  delay(300); 
162.  delay(2000);
163.  }    
164.  }
165.  else{                                     //In case the old code is wrong you can't change it
166.  lcd.clear();
167.  lcd.print("Wrong Passcode");
168.  digitalWrite(buzz, HIGH);
169.  delay(300); 
170.  digitalWrite(buzz, LOW);
171.  delay(300); 
172.  delay(2000);
173.  }
174.  }
175.  
176.  void GetNewCode1(){                      
177.    i=0;
178.    j=0;
179.  lcd.clear();
180.  lcd.print("Enter new code");                            //tell the user to enter the new code and press A
181.  lcd.setCursor(2,1);
182.  lcd.print("and press A");
183.  delay(2000);
184.  lcd.clear();
185.  lcd.setCursor(0,1);
186.  lcd.print("and press A");     
187.               
188.  while(keypressed != 'A'){            
189.  keypressed = myKeypad.getKey();
190.  if(keypressed != NO_KEY && keypressed != 'A' ){
191.  lcd.setCursor(j,0);
192.  lcd.print("*");              
193.  code_buff1[i]=keypressed;    
194.  i++;
195.  j++;                    
196.  }
197.  }
198.  keypressed = NO_KEY;
199.  }
200.  
201.  void GetNewCode2(){                         //This is exactly like the GetNewCode1 function but this time the code is stored in another array
202.    i=0;
203.    j=0;
204.  lcd.clear();
205.  lcd.print("Confirm code");
206.  lcd.setCursor(0,1);
207.  lcd.print("and press A");
208.  delay(2000);
209.  lcd.clear();
210.  lcd.setCursor(0,1);
211.  lcd.print("and press A");
212.  
213.  while(keypressed != 'A'){
214.  keypressed = myKeypad.getKey();
215.  if(keypressed != NO_KEY && keypressed != 'A' ){
216.  lcd.setCursor(j,0);
217.  lcd.print("*");
218.  code_buff2[i]=keypressed;
219.  i++;
220.  j++;                    
221.  }
222.  }
223.  keypressed = NO_KEY;
224.  }
225.  
226.  void OpenDoor()
227.  {             
228.    lcd.clear();
229.    lcd.setCursor(0,0);
230.    lcd.print("Assalamualaikum"); 
231.    delay(1000);
232.    lcd.clear();
233.    lcd.setCursor(4,0);
234.    lcd.print("Welcome");       //With a message printed
235.    lcd.setCursor(3,1);
236.    lcd.print("ATIFA mam"); 
237.    unlockbuzz();
238.    for(pos = 180; pos>=0; pos-=5) // goes from 180 degrees to 0 degrees
239.  {
240.  myservo.write(pos); // tell servo to go to position in variable 'pos'
241.  delay(5); // waits 5ms for the servo to reach the position
242.  }
243.  delay(2000);
244.  counterbeep();
245.  
246.  delay(1000);
247.  
248.  for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
249.  { // in steps of 1 degree
250.  myservo.write(pos); // tell servo to go to position in variable 'pos'
251.  delay(15);
252.  }
253.  }  
254.    
255.  void unlockbuzz()
256.  {
257.  
258.  digitalWrite(buzz, HIGH);
259.  delay(80);
260.  digitalWrite(buzz, LOW);
261.  delay(80);
262.  digitalWrite(buzz, HIGH);
263.  delay(80);
264.  digitalWrite(buzz, LOW);
265.  delay(200);
266.  digitalWrite(buzz, HIGH);
267.  delay(80);
268.  digitalWrite(buzz, LOW);
269.  delay(80);
270.  digitalWrite(buzz, HIGH);
271.  delay(80);
272.  digitalWrite(buzz, LOW);
273.  delay(80);
274.  }
275.    
276.  void counterbeep()
277.  {
278.  delay(1200);
279.  lcd.clear();
280.  digitalWrite(buzz, HIGH);
281.  lcd.setCursor(2,15);
282.  lcd.println(" ");
283.  lcd.setCursor(2,14);
284.  lcd.println(" ");
285.  lcd.setCursor(2,0);
286.  delay(200);
287.  lcd.println("GET IN WITHIN:::");
288.  lcd.setCursor(4,1);
289.  lcd.print("5");
290.  delay(200);
291.  lcd.clear();
292.  lcd.setCursor(2,0);
293.  lcd.println("GET IN WITHIN:");
294.  digitalWrite(buzz,LOW);
295.  delay(1000);        //2
296.  digitalWrite(buzz, HIGH);
297.  lcd.setCursor(2,0);
298.  lcd.println("GET IN WITHIN:");
299.  lcd.setCursor(4,1); //2
300.  lcd.print("4");
301.  delay(100);
302.  lcd.clear();
303.  lcd.setCursor(2,0);
304.  lcd.println("GET IN WITHIN:");
305.  digitalWrite(buzz,LOW);
306.  delay(1000);        //3
307.  digitalWrite(buzz, HIGH);
308.  lcd.setCursor(2,0);
309.  lcd.println("GET IN WITHIN:");
310.  lcd.setCursor(4,1); //3
311.  lcd.print("3");
312.  delay(100);
313.  lcd.clear();
314.  lcd.setCursor(2,0);
315.  lcd.println("GET IN WITHIN:");
316.  digitalWrite(buzz,LOW);
317.  delay(1000);       //4
318.  digitalWrite(buzz, HIGH);
319.  lcd.setCursor(2,0);
320.  lcd.println("GET IN WITHIN:");
321.  lcd.setCursor(4,1); //4
322.  lcd.print("2");
323.  delay(100);
324.  lcd.clear();
325.  lcd.setCursor(2,0);
326.  lcd.println("GET IN WITHIN:");
327.  digitalWrite(buzz,LOW);
328.  delay(1000);
329.  digitalWrite(buzz, HIGH);
330.  lcd.setCursor(4,1);
331.  lcd.print("1");
332.  delay(100);
333.  lcd.clear();
334.  lcd.setCursor(2,0);
335.  lcd.println("GET IN WITHIN::");
336.  digitalWrite(buzz,LOW);
337.  delay(1000);      //5
338.  digitalWrite(buzz, HIGH);
339.  delay(40);
340.  digitalWrite(buzz,LOW);
341.  delay(40);
342.  digitalWrite(buzz, HIGH);
343.  delay(40);
344.  digitalWrite(buzz,LOW);
345.  delay(40);
346.  digitalWrite(buzz, HIGH);
347.  delay(40);
348.  digitalWrite(buzz,LOW);
349.  delay(40);
350.  digitalWrite(buzz, HIGH);
351.  delay(40);
352.  digitalWrite(buzz,LOW);
353.  lcd.clear();
354.  lcd.setCursor(2,0);
355.  lcd.print("RE-LOCKING");
356.  delay(500);
357.  lcd.setCursor(12,0);
358.  lcd.print(".");
359.  delay(500);
360.  lcd.setCursor(13,0);
361.  lcd.print(".");
362.  delay(500);
363.  lcd.setCursor(14,0);
364.  lcd.print(".");
365.  delay(400);
366.  lcd.clear();
367.  lcd.setCursor(4,0);
368.  lcd.print("LOCKED!");
369.  delay(440);
370.  
371.  }
1.  #include <Keypad.h>
2.  #include <EEPROM.h>
3.  #include <LiquidCrystal.h>
4.  #include <Servo.h>
5.  
6.  Servo myservo;
7.  int pos=0;
8.  const byte numRows= 4;          
9.  const byte numCols= 4;         
10. 
11. char keymap[numRows][numCols]= 
12. {
13. {'1', '2', '3', 'A'}, 
14. {'4', '5', '6', 'B'}, 
15. {'7', '8', '9', 'C'},
16. {'*', '0', '#', 'D'}
17. };
18. 
19. char keypressed;                 
20. char code[]= {'6','6','B','1'};
21. char code_buff1[sizeof(code)];
22. char code_buff2[sizeof(code)];  
23. 
24. short a=0,i=0,s=0,j=0;         
25. 
26. byte rowPins[numRows] = {0,1,2,3}; 
27. byte colPins[numCols]= {4,5,6,7}; 
28. int buzz=8;
29. LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
30. Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
31. 
32. void setup()
33. {
34. pinMode(buzz, OUTPUT);
35. myservo.attach(9);
36. lcd.begin (16,2);
37. lcd.setCursor(0,0);
38. lcd.print("PROJECT  MADE BY"); 
39. lcd.setCursor(1,1);   
40. lcd.print("AYESHA PARVEEN"); 
41. delay(2000);
42. lcd.clear();
43. lcd.setCursor(0,0);
44. lcd.print("Press * to_/door");
45. lcd.setCursor(0,1);
46. lcd.print("Press#tochg pass");
47. }
48. void loop()
49. {
50. keypressed = myKeypad.getKey();              
51. if(keypressed == '*'){                   
52. lcd.clear();
53. lcd.setCursor(1,0);
54. lcd.print("Enter passcode");
55. lcd.setCursor(2,1);
56. lcd.print("and press A");
57. delay(2000);
58. lcd.clear();
59. lcd.setCursor(2,0);
60. lcd.print("and press A");  
61. GetCode();                          
62. if(a==sizeof(code))          
63. OpenDoor();
64. else{
65. lcd.clear();               
66. lcd.print("Wrong passcode");
67. delay(1000);
68. lcd.clear4(); 
69. lcd.setCursor(4,0);
70. lcd.print("You are");
71. lcd.setCursor(2,1);
72. lcd.print("Unauthorized");                    
73. digitalWrite(buzz, HIGH);
74. }
75. delay(2000);
76. lcd.clear();
77. digitalWrite(buzz,LOW);
78. lcd.setCursor(0,0);
79. lcd.print("Press * to_/door");
80. lcd.setCursor(0,1);
81. lcd.print("Press#tochg pass");
82. }
83. 
84. if(keypressed == '#')
85. {                  
86. ChangeCode();
87. lcd.clear();
88. lcd.setCursor(0,0);
89. lcd.print("Press * to_/door");
90. lcd.setCursor(0,1);
91. lcd.print("Press#tochg pass");
92. }         
93. }
94. 
95. void GetCode(){                         //Getting code sequence
96.        i=0;                                       //All variables set to 0
97.        a=0; 
98.        j=0; 
99.                                      
100.  while(keypressed != 'A'){                                            //The user press A to confirm the code otherwise he can keep typing
101.  keypressed = myKeypad.getKey();                         
102.  if(keypressed != NO_KEY && keypressed != 'A' ){            
103.  lcd.setCursor(j,1);                                                       //This to write "*" on the LCD whenever a key is pressed it's position is controlled by j
104.  lcd.print("*");
105.  j++;
106.  if(keypressed == code[i]&& i<sizeof(code)){             //if the char typed is correct a and i increments to verify the next caracter
107.  a++;                                                                         //Now I think maybe I should have use only a or i ... too lazy to test it -_-'
108.  i++;
109.  }
110.  else
111.  a--;                                                      //if the character typed is wrong a decrements and cannot equal the size of code []
112.  }
113.  }
114.  keypressed = NO_KEY;
115.  }
116.  void ChangeCode(){                      //Change code sequence
117.  lcd.clear();
118.  lcd.print("Changing code");
119.  delay(1000);
120.  lcd.clear();
121.  lcd.print("Enter old code");
122.  lcd.setCursor(2,1);
123.  lcd.print("and press A");
124.  delay(2000);
125.  lcd.clear();
126.  lcd.setCursor(2,0);
127.  lcd.print("and press A");  
128.  GetCode();                                   //verify the old code first so you can change it
129.  if(a==sizeof(code)){                   //again verifying the a value
130.  lcd.clear();
131.  lcd.print("Changing code");
132.  GetNewCode1();                      //Get the new code
133.  GetNewCode2();                     //Get the new code again to confirm it
134.  s=0;
135.  for(i=0 ; i<sizeof(code) ; i++){                   //Compare codes in array 1 and array 2 from two previous functions
136.  if(code_buff1[i]==code_buff2[i])
137.  s++;                                                        //again this how we verifiy, increment s whenever codes are matching
138.  }
139.  if(s==sizeof(code))
140.  {             
141.  for(i=0 ; i<sizeof(code) ; i++){
142.  code[i]=code_buff2[i];         
143.  EEPROM.put(i, code[i]);
144.  }
145.  lcd.clear();
146.  lcd.print("Code Changed");
147.  digitalWrite(buzz, HIGH);
148.  delay(300); 
149.  digitalWrite(buzz, LOW);
150.  delay(300);
151.  delay(2000);
152.  }
153.  else{                         //In case the new codes aren't matching
154.  lcd.clear();
155.  lcd.print("Codes are not");
156.  lcd.setCursor(4,1);
157.  lcd.print("matching !!");
158.  digitalWrite(buzz, HIGH);
159.  delay(300); 
160.  digitalWrite(buzz, LOW);
161.  delay(300); 
162.  delay(2000);
163.  }    
164.  }
165.  else{                                     //In case the old code is wrong you can't change it
166.  lcd.clear();
167.  lcd.print("Wrong Passcode");
168.  digitalWrite(buzz, HIGH);
169.  delay(300); 
170.  digitalWrite(buzz, LOW);
171.  delay(300); 
172.  delay(2000);
173.  }
174.  }
175.  
176.  void GetNewCode1(){                      
177.    i=0;
178.    j=0;
179.  lcd.clear();
180.  lcd.print("Enter new code");                            //tell the user to enter the new code and press A
181.  lcd.setCursor(2,1);
182.  lcd.print("and press A");
183.  delay(2000);
184.  lcd.clear();
185.  lcd.setCursor(0,1);
186.  lcd.print("and press A");     
187.               
188.  while(keypressed != 'A'){            
189.  keypressed = myKeypad.getKey();
190.  if(keypressed != NO_KEY && keypressed != 'A' ){
191.  lcd.setCursor(j,0);
192.  lcd.print("*");              
193.  code_buff1[i]=keypressed;    
194.  i++;
195.  j++;                    
196.  }
197.  }
198.  keypressed = NO_KEY;
199.  }
200.  
201.  void GetNewCode2(){                         //This is exactly like the GetNewCode1 function but this time the code is stored in another array
202.    i=0;
203.    j=0;
204.  lcd.clear();
205.  lcd.print("Confirm code");
206.  lcd.setCursor(0,1);
207.  lcd.print("and press A");
208.  delay(2000);
209.  lcd.clear();
210.  lcd.setCursor(0,1);
211.  lcd.print("and press A");
212.  
213.  while(keypressed != 'A'){
214.  keypressed = myKeypad.getKey();
215.  if(keypressed != NO_KEY && keypressed != 'A' ){
216.  lcd.setCursor(j,0);
217.  lcd.print("*");
218.  code_buff2[i]=keypressed;
219.  i++;
220.  j++;                    
221.  }
222.  }
223.  keypressed = NO_KEY;
224.  }
225.  
226.  void OpenDoor()
227.  {             
228.    lcd.clear();
229.    lcd.setCursor(0,0);
230.    lcd.print("Assalamualaikum"); 
231.    delay(1000);
232.    lcd.clear();
233.    lcd.setCursor(4,0);
234.    lcd.print("Welcome");       //With a message printed
235.    lcd.setCursor(3,1);
236.    lcd.print("ATIFA mam"); 
237.    unlockbuzz();
238.    for(pos = 180; pos>=0; pos-=5) // goes from 180 degrees to 0 degrees
239.  {
240.  myservo.write(pos); // tell servo to go to position in variable 'pos'
241.  delay(5); // waits 5ms for the servo to reach the position
242.  }
243.  delay(2000);
244.  counterbeep();
245.  
246.  delay(1000);
247.  
248.  for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
249.  { // in steps of 1 degree
250.  myservo.write(pos); // tell servo to go to position in variable 'pos'
251.  delay(15);
252.  }
253.  }  
254.    
255.  void unlockbuzz()
256.  {
257.  
258.  digitalWrite(buzz, HIGH);
259.  delay(80);
260.  digitalWrite(buzz, LOW);
261.  delay(80);
262.  digitalWrite(buzz, HIGH);
263.  delay(80);
264.  digitalWrite(buzz, LOW);
265.  delay(200);
266.  digitalWrite(buzz, HIGH);
267.  delay(80);
268.  digitalWrite(buzz, LOW);
269.  delay(80);
270.  digitalWrite(buzz, HIGH);
271.  delay(80);
272.  digitalWrite(buzz, LOW);
273.  delay(80);
274.  }
275.    
276.  void counterbeep()
277.  {
278.  delay(1200);
279.  lcd.clear();
280.  digitalWrite(buzz, HIGH);
281.  lcd.setCursor(2,15);
282.  lcd.println(" ");
283.  lcd.setCursor(2,14);
284.  lcd.println(" ");
285.  lcd.setCursor(2,0);
286.  delay(200);
287.  lcd.println("GET IN WITHIN:::");
288.  lcd.setCursor(4,1);
289.  lcd.print("5");
290.  delay(200);
291.  lcd.clear();
292.  lcd.setCursor(2,0);
293.  lcd.println("GET IN WITHIN:");
294.  digitalWrite(buzz,LOW);
295.  delay(1000);        //2
296.  digitalWrite(buzz, HIGH);
297.  lcd.setCursor(2,0);
298.  lcd.println("GET IN WITHIN:");
299.  lcd.setCursor(4,1); //2
300.  lcd.print("4");
301.  delay(100);
302.  lcd.clear();
303.  lcd.setCursor(2,0);
304.  lcd.println("GET IN WITHIN:");
305.  digitalWrite(buzz,LOW);
306.  delay(1000);        //3
307.  digitalWrite(buzz, HIGH);
308.  lcd.setCursor(2,0);
309.  lcd.println("GET IN WITHIN:");
310.  lcd.setCursor(4,1); //3
311.  lcd.print("3");
312.  delay(100);
313.  lcd.clear();
314.  lcd.setCursor(2,0);
315.  lcd.println("GET IN WITHIN:");
316.  digitalWrite(buzz,LOW);
317.  delay(1000);       //4
318.  digitalWrite(buzz, HIGH);
319.  lcd.setCursor(2,0);
320.  lcd.println("GET IN WITHIN:");
321.  lcd.setCursor(4,1); //4
322.  lcd.print("2");
323.  delay(100);
324.  lcd.clear();
325.  lcd.setCursor(2,0);
326.  lcd.println("GET IN WITHIN:");
327.  digitalWrite(buzz,LOW);
328.  delay(1000);
329.  digitalWrite(buzz, HIGH);
330.  lcd.setCursor(4,1);
331.  lcd.print("1");
332.  delay(100);
333.  lcd.clear();
334.  lcd.setCursor(2,0);
335.  lcd.println("GET IN WITHIN::");
336.  digitalWrite(buzz,LOW);
337.  delay(1000);      //5
338.  digitalWrite(buzz, HIGH);
339.  delay(40);
340.  digitalWrite(buzz,LOW);
341.  delay(40);
342.  digitalWrite(buzz, HIGH);
343.  delay(40);
344.  digitalWrite(buzz,LOW);
345.  delay(40);
346.  digitalWrite(buzz, HIGH);
347.  delay(40);
348.  digitalWrite(buzz,LOW);
349.  delay(40);
350.  digitalWrite(buzz, HIGH);
351.  delay(40);
352.  digitalWrite(buzz,LOW);
353.  lcd.clear();
354.  lcd.setCursor(2,0);
355.  lcd.print("RE-LOCKING");
356.  delay(500);
357.  lcd.setCursor(12,0);
358.  lcd.print(".");
359.  delay(500);
360.  lcd.setCursor(13,0);
361.  lcd.print(".");
362.  delay(500);
363.  lcd.setCursor(14,0);
364.  lcd.print(".");
365.  delay(400);
366.  lcd.clear();
367.  lcd.setCursor(4,0);
368.  lcd.print("LOCKED!");
369.  delay(440);
370.  
371.  }
