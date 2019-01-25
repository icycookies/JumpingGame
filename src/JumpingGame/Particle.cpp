#include "JumpingGame.h"
#include<ctime>
using namespace std;
const double pi=acos(-1);
extern Stage* currentStage;
extern Hero* theHero;
extern vector<Particle*> particles;
extern bool skip_particle;
Particle* CreateParticle(double x,double y,double vx,double vy,int type,Col col){
	Particle* particle=new Particle();
	particle->x=x;
	particle->y=y;
	particle->vx=vx;
	particle->vy=vy;
	particle->type=type;
	particle->col=col;
	particle->time=0;
	return particle;
}
void UpdateParticles(){
	int n=particles.size();
	vector<Particle*>::iterator i=particles.begin();
	for (;i!=particles.end();){
		Particle* particle=*i;
		particle->x+=particle->vx;
		particle->y+=particle->vy;
		if (particle->type==1)particle->vy+=GRAVITY/2;
		if (particle->type==3){
			particle->vy=(rand()%1000-500)*1.0/200;
			particle->time++;
			if (particle->time>30){
				particles.erase(i);
				delete particle;
				if (particles.empty())break;else continue;
			}
		}
		if (particle->type==5){
			particle->time++;
			particle->y+=sin(particle->time*1.0/50*pi)*2;
		}
		if (particle->x<0||particle->x>max(currentStage->m*BLOCK_SIZE_X,WINDOW_WIDTH)||particle->y<0||particle->y>max(currentStage->n*BLOCK_SIZE_Y,WINDOW_HEIGHT)){
			particles.erase(i);
			if (particles.empty()){delete particle;break;}
			if (particle->type==2)CreateAnimation(1,1,0,0);
			if (particle->type==4)CreateAnimation(5,1,0,0);
			if (particle->type==5)CreateAnimation(6,1,0,0);
			delete particle;
		}else i++;
	}
}
void CreateAnimation(int type,int cnt,double x,double y){
	if (skip_particle)return;
	if (type==0){
		Col col;col.R=135,col.G=206,col.B=235;
		for (int i=0;i<cnt;i++){
			double vx=(rand()%1000-500)*1.0/200;
			double vy=-rand()%1000*1.0/200;
			particles.push_back(CreateParticle(x,y,vx,vy,1,col));
		}
	}
	if (type==1){
		for (int i=0;i<cnt;i++){
			double x=rand()%1600*1.0;
			double v=rand()%1000*1.0/500+2.0;
			Col col;col.R=col.G=col.B=255;
			if (x<=1000)particles.push_back(CreateParticle(x,0,-v,v,2,col));
			else particles.push_back(CreateParticle(1000,x-1000,-v,v,2,col));
		}
	}
	if (type==2){
		Col col;col.R=255,col.G=0,col.B=0;
		for (int i=0;i<cnt;i++){
			double vx=(rand()%1000-500)*1.0/200;
			double vy=(rand()%1000-500)*1.0/100;
			particles.push_back(CreateParticle(x,y,vx,vy,1,col));
		}
	}
	if (type==3){
		Col col;col.R=135,col.G=206,col.B=235;
		for (int i=0;i<cnt;i++){
			double vx=rand()%1000*1.0/1000+0.2;
			if (theHero->direction)vx=-vx;
			particles.push_back(CreateParticle(x,y,vx,0,3,col));
		}
	}
	if (type==4){
		Col col;col.R=255,col.G=255,col.B=0;
		for (int i=0;i<cnt;i++){
			double vx=(rand()%1000-500)*1.0/200;
			double vy=-rand()%1000*1.0/200;
			particles.push_back(CreateParticle(x,y,vx,vy,1,col));
		}
	}
	if (type==5){
		Col col;col.R=col.G=col.B=150;
		for (int i=0;i<cnt;i++){
			double x=rand()%1000,y=0;
			if (cnt>1)y=rand()%600;
			double vx=rand()%1000*1.0/200-2,vy=rand()%1000*1.0/100+10;
			particles.push_back(CreateParticle(x,y,vx,vy,4,col));
		}
	}
	if (type==6){
		for (int i=0;i<cnt;i++){
			Col col;col.R=col.G=col.B=rand()%100+150;
			double x=1000,y=rand()%600;
			double vx=-rand()%600*1.0/100-2;
			if (cnt>1)x=rand()%1000;
			particles.push_back(CreateParticle(x,y,vx,0,5,col));
		}
	}
}