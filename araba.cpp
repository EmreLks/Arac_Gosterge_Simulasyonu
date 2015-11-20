#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Araba
{

public:

		float hiz,toplam_km,gunluk_km,devir,yakit,toplamhiz,hararet,sayac,islem,sonuc;
		int vites,sure;
		BITMAP *ok,*ok1,*ara,*panel;
		FONT *myfont,*myfontb;
		PALETTE palette;
		
   
		Araba(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float tkm)
		{
		   devir=0.0;
           hiz=0.0;
           gunluk_km=0.0;
           toplam_km=tkm;
		   vites=1;
		   ok=o;
		   ara=index;
		   panel=p;
		   ok1=o1;
		   yakit=140;
		   toplamhiz=0;
		   hararet=0;
		   sayac=0;
		   islem=0;
		   sonuc=0;
		}
      	
private:

		float hiz_dondur(float d,int v)
		{
			return 1.74*(d/3.647/disli_dondur(v)/1000)*60;
		}

        
public:

		void Ciz()
		{
          
           char x[]="km/h";
           myfont=load_font("font/7.pcx",palette,NULL);
           myfontb=load_font("font/13.pcx",palette,NULL);
		   BITMAP *fren=load_bitmap("bmp/abs.bmp",NULL);
           sonuc=gunluk_km+toplam_km;
           gunluk_km=(toplamhiz+sayac)/10000;
           islem=(toplamhiz+sayac)/10000;
           clear_to_color(ara,makecol(255,0,255)); 
           blit(panel,ara,0,0,0,0,1000,357);

		   if(key[KEY_DOWN])
		   {
			   blit(fren,ara,0,0,450,200,1000,357);
		   }


           textprintf_ex(ara,myfontb,238,250,makecol(255,0,0),makecol(255,255,255),"%.2f",gunluk_km);
           textprintf_ex(ara,myfont,272,295,makecol(255,0,0),makecol(255,255,255),"%s",x);
           textprintf_ex(ara,myfontb,645,219,makecol(255,0,0),makecol(0,255,0),"%d",vites);
           textprintf_ex(ara,myfontb,600,270,makecol(255,0,0),makecol(255,255,255),"%.2f",sonuc);
           textprintf_ex(ara,myfont,650,310,makecol(255,0,0),makecol(255,255,255),"%s",x);
           rotate_sprite(ara,ok,560,160,ftofix((hiz*1.16)*178/255-30));
           rotate_sprite(ara,ok,190,160,ftofix((devir*4)/100*178/255-35));
           rotate_sprite(ara,ok1,410,120,ftofix(yakit*178/256));
           rotate_sprite(ara,ok1,790,260,ftofix(((hararet*sayac)/5000)*178/256+30));

		   //textprintf(ara,myfont,100,330,makecol(0,255,0),"devirrrr: %.2f hiz: %.2f vites: %d gunluk_km: %.2f yakit: %f hararet: %f toplam_km %f",devir,hiz,vites,gunluk_km,yakit,hararet,sonuc);

         }

		

///////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Hareket()
		{
            
            if(yakit>50 && !key[KEY_SPACE] && hararet<128)
             {
				if(key[KEY_UP])
			    {

                    toplamhiz=toplamhiz+hiz;
                    sayac+=1;
                    hararet=hararet+0.02;
					if(devir<7000 && hiz<300)
					{
                            hararet=hararet+0.02;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
							devir+=10;
							if(devir<6000)
							{
                                sayac+=1;
								devir+=10;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.02;
							}
							if(devir>6100 && devir<6500 && vites<5)
							{
                                sayac+=1.2;
								vites++;
								

								devir=devir-2000;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.05;
							}
							if(devir>6550 && vites==5)
							{
                                sayac+=1.6;
								devir++;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.1;
							}
					}
				}

				else if(key[KEY_DOWN] && devir>900 && hiz>0 && vites>0)
				{
                    sayac+=0.3;
					devir=devir-100;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					hararet=hararet-0.01;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+3000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}

					
					}
				
				
				}
				else if(!key[KEY_UP] && !key[KEY_DOWN] && devir>900 && hiz>0 && vites>0)
				{	
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-10;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}
				}	
       }
     else if((yakit<=50 || hararet>128) && devir>0 && hiz>0 && vites>0)
     {
     
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-10;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}
    }
    else if(key[KEY_SPACE] && devir>100 && hiz>0 && vites>0)
    {
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-100;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}



    }

   }

private:

	float disli_dondur(int a)
	{
			
			switch(a)
			{
			  case 1:
				  return 3.94182;
			  case 2:
				  return 2.6701;
			  case 3:
				  return 1.8087;
			  case 4:
				  return 1.2252;
			  case 5:
				  return 0.830;

			}
			
	}
		
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Kontroller: public Araba
{
	private:
			BITMAP *benzin,*uzun_acik,*kisa_acik,*uzun_kapali,*kisa_kapali,*sol,*sag;
		    int far_durum,sinyal_durum;
        
	public:
		    Kontroller(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Araba(o,index,p,o1,t_km)
			{
			    far_durum=0;
				sinyal_durum=0;
			}

//////////////////////////////////////////////////
			void sinyal_kontrol(int durum)
		{

			//textprintf(ara,myfont,10,10,makecol(0,255,0),"sinyal_durumum=%d sure=%d ",sinyal_durum,sure);

			if(sure%2==0)
			{
			
			if(sinyal_durum==1)
            {
                blit(sol,ara,0,0,377,8,1000,340);
				
            }
            else if(sinyal_durum==2)
            {
                blit(sag,ara,0,0,534,8,1000,340);
				
            }
            else if(sinyal_durum==3)
            {
                 blit(sol,ara,0,0,377,8,1000,340);
                 blit(sag,ara,0,0,534,8,1000,340);
				 
            }
			}
		}
/////////////////////////////////////////////////////////////////////
        void Ciz()
        {
            Araba::Ciz();
			////////////////////////////////////////////////////////
			benzin=load_bitmap("bmp/benzin_bitti.bmp",NULL);
            sol=load_bitmap("bmp/sol.bmp",NULL);
            sag=load_bitmap("bmp/sag.bmp",NULL);
            uzun_acik=load_bitmap("bmp/uzun_acik.bmp",NULL);
            kisa_acik=load_bitmap("bmp/kisa_acik.bmp",NULL);
            uzun_kapali=load_bitmap("bmp/uzun_kapali.bmp",NULL);
            kisa_kapali=load_bitmap("bmp/kisa_kapali.bmp",NULL);
			//////////////////////////////////////////////////////////
            
            if(key[KEY_L])
            {
                far_durum=0;
            }
            if(key[KEY_K])
            {
                 far_durum=1;
            }
            if(key[KEY_U])
            {
                 far_durum=2;
            }
            if(key[KEY_I])
            {
                 far_durum=3;
            }
            if(far_durum==0)
            {
                 blit(kisa_kapali,ara,0,0,447,170,1000,357);
            }
            if(far_durum==1)
            {
                 blit(kisa_acik,ara,0,0,447,170,1000,357);
            }
            if(far_durum==2)
            {
                 blit(uzun_acik,ara,0,0,413,168,1000,357);
            }
            if(far_durum==3)
            {
                 blit(uzun_kapali,ara,0,0,413,168,1000,357);
            }
            
           
			if((sinyal_durum==1 && key[KEY_A]) || (sinyal_durum==2 && key[KEY_D]) || (sinyal_durum==3 && key[KEY_S]))
			{
				sinyal_durum=0;
				rest(250); 
			}

			else
			{
            if(key[KEY_A])
            {
                sinyal_durum=1;
				rest(250);
				
            }
            else if(key[KEY_D])
            {
                sinyal_durum=2;
				rest(250);
				 
            }
            else if(key[KEY_S])
            {
                 sinyal_durum=3;
				rest(250);

            }
			}
			sinyal_kontrol(sinyal_durum);









            if(yakit<50)
            {
                       yakit=49;
                       blit(benzin,ara,0,0,414,251,1000,357);
            }
            else
            {
               yakit=140-(islem*1.2);
            }
            
           
            
        }
///////////////////////////////////////////////////////////////////////
        float km_cevir()
        {
            return sonuc;
        }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Secenekler: public Kontroller
{
	private:

		BITMAP *elfren,*korna,*dortlu,*hararet_s,*park,*sison,*sisarka;
        SAMPLE *ses;

    public:
		 Secenekler(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Kontroller(o,index,p,o1,t_km)
        {
            
        }
		 void Ciz()
		 {
			Kontroller::Ciz();
		    /////////////////////////////////////////////////////
		    elfren=load_bitmap("bmp/elfren.bmp",NULL);
            hararet_s=load_bitmap("bmp/hararet.bmp",NULL);
            dortlu=load_bitmap("bmp/dortlu.bmp",NULL);
			park=load_bitmap("bmp/park.bmp",NULL);
			sison=load_bitmap("bmp/sison.bmp",NULL);
            sisarka=load_bitmap("bmp/sisarka.bmp",NULL);
           
			/////////////////////////////////////////////

			if(key[KEY_SPACE])
            {
               blit(elfren,ara,0,0,431,251,1000,357);
            }

			if(key[KEY_4])
            {
               blit(sison,ara,0,0,493,249,1000,340);
            }

            if(key[KEY_5])
            {
               blit(dortlu,ara,0,0,462,248,1000,357);
            }

			if(key[KEY_6])
            {
               blit(sisarka,ara,0,0,481,168,1000,340);
            }
			
            
            if(key[KEY_P])
            {
               blit(park,ara,0,0,485,204,1000,357);
            }
           
			
			if(hararet>128)
            {
                blit(hararet_s,ara,0,0,413,200,1000,357);
            }

			/////////////////////////////////////////

			blit(ara,screen,0,0,0,0,1000,357);
		 }

};