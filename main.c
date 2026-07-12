#include <stdio.h>
#include <math.h>

float calc_alt(float p,float p0)
{
    float alt;
    alt=44330*(1-pow(p/p0,1/5.25588));
    return alt;
}
int counter(float prev2_alt,float prev1_alt,float current_alt)
{
  
   if (prev2_alt-prev1_alt==0 && prev1_alt-current_alt==0)
   {
       return 1;//for apogee
   }
   if(prev2_alt-prev1_alt>0 && prev1_alt-current_alt>0)
   {
       return 2;//for descent
   }
   if(prev2_alt-prev1_alt<0 && prev1_alt-current_alt<0)
   {
       return 3;//for ascent
   }
   return 0;
    
}
//the values can be printed according to the resolution given to us in the mission guide
int main()
{
    enum state { LAUNCH_PAD,ASCENT,APOGEE,DESCENT,PROBE_RELEASE,PAYLOAD_RELEASE,LANDED };
    enum state s=LAUNCH_PAD;
    float sum=0;
    int count=0;
    float threshold,p0,current_alt,prev1_alt,prev2_alt,apogee,p;
   while(1)
   {
       switch(s)
       {
           case LAUNCH_PAD:
           while(count<10)// 10 is just a example no. i am trying to find the best value of p0 by taking avg of all the incoming values of it
    {
        scanf("%f",&p);//p is the value coming from the sensor
        sum=sum+p;
        count++;
    }
    p0=(float)sum/10;
    prev2_alt=0;
    prev1_alt=0;
    current_alt=0;
    s=ASCENT;
           break;
           case ASCENT:
           prev2_alt=prev1_alt;
           prev1_alt=current_alt;
           scanf("%f",&p);
           current_alt=calc_alt(p,p0);
           
           int c=counter(prev2_alt,prev1_alt,current_alt);
           
           if(c==3)
           {
               apogee=current_alt;
           }
           else if(c==1||c==2) 
           {
               s=APOGEE;
               break;
           }
           
           break;
           case APOGEE:
           //apogee is reached
            prev2_alt=prev1_alt;
           prev1_alt=current_alt;
           scanf("%f",&p);
           current_alt=calc_alt(p,p0);
           threshold=(float)(80*apogee)/100;
           
           s=DESCENT;   
          
         
         break;
           case DESCENT:
            prev2_alt=prev1_alt;
           prev1_alt=current_alt;
           scanf("%f",&p);
           current_alt=calc_alt(p,p0);
           
               if(current_alt<=threshold)
               {
                  // probe release mechanism
                  s=PROBE_RELEASE;
               break;
               }
               
           break;
           case PROBE_RELEASE:
             prev2_alt=prev1_alt;
           prev1_alt=current_alt;
           scanf("%f",&p);
           current_alt=calc_alt(p,p0);
           if (current_alt<=2.0)
               {
                 //  payload release mechanism
                 s=PAYLOAD_RELEASE;
                 break;
               }
           break;
           case PAYLOAD_RELEASE:
           prev2_alt=prev1_alt;
           prev1_alt=current_alt;
           scanf("%f",&p);
           current_alt=calc_alt(p,p0);
           if(prev2_alt-prev1_alt==0&&prev1_alt-current_alt==0)//it should be approx 0 bcz due to sensor noise we might not get an exact 0. i haven't figured out how to write that part yet so i took the exact value for now
           s=LANDED;
           break;
           case LANDED:
           printf("succesfully landed");
          return 0;
           default:  
           printf("the mission ended abruptly due to unavoidable circumstances");
           return 0;
           break;
       }
   }
}
