#define led1 1
#define led2 4
#define rand_pin A0
#define fluctuation 10
byte rand_number[]={1,1};
byte new_rand_number[]={1,1};
byte max_range=255;
byte min_range=0;

byte count_range(byte min, byte max, byte down_range, byte up_range){
  if(min<down_range){
    min=down_range;
  }

  if(max>up_range){
    max=up_range;
  }
  return min, max;
}

void go_to_the_value(byte step, byte step_time, byte u_value, byte the_value, byte pin){
  if(u_value<the_value){
    for(byte i=u_value; i<=the_value; i+=step){
      analogWrite(pin, i);
      delay(step_time);
    } 
  }else{
    for(byte i=u_value; i<=the_value; i-=step){
      analogWrite(pin, i);
      delay(step_time);
    }
  }
}

void func_for_one_led(byte n_in_table, byte pin_n){
  min_range, max_range=count_range(rand_number[n_in_table]-fluctuation, rand_number[n_in_table]+fluctuation, 1,255);
  new_rand_number[n_in_table]=random(min_range, max_range);
  if(new_rand_number[n_in_table]<rand_number[n_in_table]){
    go_to_the_value( 1, 60, rand_number[n_in_table], new_rand_number[n_in_table], pin_n);
  }else{
    go_to_the_value( 1, 30, rand_number[n_in_table], new_rand_number[n_in_table], pin_n);
  }
  rand_number[n_in_table]=new_rand_number[n_in_table];
}

void setup(){
  pinMode(3,OUTPUT);
  pinMode(A0,INPUT);
  randomSeed(analogRead(rand_pin));
  rand_number[0]=random(min_range,max_range);
  rand_number[1]=random(min_range,max_range);
  go_to_the_value(1, 15, 0, rand_number[0], led1);
  go_to_the_value(1, 15, 0, rand_number[1], led2);
  new_rand_number[0]=rand_number[0];
  new_rand_number[1]=rand_number[1];
  
}

void loop(){
  func_for_one_led(0, led1);
  func_for_one_led(1, led2);
}
