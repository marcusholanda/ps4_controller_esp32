#include <PS4Controller.h>

#define PWMA 19
#define PWMB 27
#define A1  5
#define A2  32
#define B1  25
#define B2  26
#define stby 33

void motors_control(int linear, int angular) {
  angular = pid(angular, - get_theta_speed());
  int Vel_R = linear - angular; //ao somar o angular com linear em cada motor conseguimos a ideia de direcao do robo
  int Vel_L = linear + angular;
  
  if(Vel_R<15 && Vel_R>-15) Vel_R=0; 
  if(Vel_R>255 ) Vel_R=255;
  if(Vel_R<-255) Vel_R=-255;  

  if(Vel_L<15 && Vel_L>-15) Vel_L=0;
  if(Vel_L>255 ) Vel_L=255;
  if(Vel_L<-255) Vel_L=-255;
  motor_R(Vel_R); //manda para a funcao motor um valor de -255 a 255, o sinal signifca a direcao
  //Serial.print(Vel_R);
  //Serial.print(" ");
  motor_L(Vel_L);
  //Serial.println(Vel_L);

}

void motor_R(int speedA){  // se o valor for positivo gira para um lado e se for negativo troca o sentido
  if(speedA>0){  
    digitalWrite(A1, 1);
    digitalWrite(A2, 0);
  }else{
    digitalWrite(A1, 0);
    digitalWrite(A2, 1);
  }
  ledcWrite(1,abs( speedA));
}
void motor_L(int speedB){
  if(speedB>0){
    digitalWrite(B1, 1);
    digitalWrite(B2, 0);
  }else{
    digitalWrite(B1, 0);
    digitalWrite(B2, 1);
  }
  ledcWrite(2,abs( speedB));
}




void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Start");
  PS4.begin("94:F6:D6:79:F5:34");

  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);

  ledcSetup(1, 80000, 8);
  ledcSetup(2, 80000, 8);

  pinMode(stby, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  digitalWrite(stby, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(B1, 0);
  digitalWrite(B2, 0);

  mpu_init();


}

void loop() {

 
  if (PS4.isConnected()) {
  // estou multiplicando por 1.8 para aumentar a velocidade linear, o quao rapido o robo vai ser
  // estou dividindo por 2 o angular, para o robô fazer menos curva e ser mais facil de controlar
  
  //motors_control(linear_speed*multiplicador, angular_speed* multiplicador2); 
    motors_control(PS4.LStickY()*1.8, PS4.RStickX()*2);
    Serial.println(get_theta_speed());

  }





}
