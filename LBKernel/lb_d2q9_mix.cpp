/*
 * Created by Waipot Ngamsaad (ngamsaad.waipot@gmail.com)
 * Dated 25-01-2009

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <fstream>

#ifdef USE_GRAPHICS
#include <mgl/mgl_fltk.h>
#include "lb_viewer.h"
extern "C" {
#include <mygraph.h>
}
#endif

#include "lb_d2q9_mix.h"

namespace TINY_LB
{

	#define fourOnine (4./9.)
	#define oneOnine  (1./9.)
	#define oneOthirtysix (1./36.)

	LBD2Q9Mix::LBD2Q9Mix(int nx, int ny)
	: LBD2Q9(nx,ny,2)
	{
		omega = new real[RANK];

		omega[0] = 1.;
		omega[1] = 1.;

		rho = new real[NNODE];
		phi = new real[NNODE];

		U = new real[2*NNODE];
	
		const real M[9][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
    		{-4, -1, -1, -1, -1, 2, 2, 2, 2},
    		{4, -2, -2, -2, -2, 1, 1, 1, 1},
    		{0, 1, 0, -1, 0, 1, -1, -1, 1},
    		{0, -2, 0, 2, 0, 1, -1, -1, 1},
    		{0, 0, 1, 0, -1, 1, 1, -1, -1},
    		{0, 0, -2, 0, 2, 1, 1, -1, -1},
    		{0, 1, -1, 1, -1, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 1, -1, 1, -1}};

		const real invM[9][9] = {
		{1./9., -1./9., 1./9., 0., 0., 0., 0., 0., 0.},
       		{1./9., -1./36., -1./18., 1./6., -1./6., 0., 0., 1./4., 0.},
       		{1./9., -1./36., -1./18., 0., 0., 1./6., -1./6., -1./4., 0.},
       		{1./9., -1./36., -1./18., -1./6., 1./6., 0., 0., 1./4., 0.},
       		{1./9., -1./36., -1./18., 0., 0., -1./6., 1./6., -1./4., 0.},
       		{1./9., 1./18., 1./36., 1./6., 1./12., 1./6., 1./12., 0., 1./4.},
       		{1./9., 1./18., 1./36., -1./6., -1./12., 1./6., 1./12., 0., -1./4.},
       		{1./9., 1./18., 1./36., -1./6., -1./12., -1./6., -1./12., 0., 1./4.},
       		{1./9., 1./18., 1./36., 1./6.,  1./12., -1./6., -1./12., 0., -1./4.}};

		const real S[9] = {0.,1.,1.,0.,1.,0.,1.,1.,1.};

		real Ctmp[9][9];

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				Ctmp[i][j] = 0;
				C[i][j] = 0;

				std::cout<< "M[" <<i <<"][" <<j <<"] = " <<M[i][j] <<" ";
			}
			std::cout <<std::endl;
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					Ctmp[i][j] += S[i]*M[k][j];
				}

				std::cout<< "invM[" <<i <<"][" <<j <<"] = " <<invM[i][j] <<" ";
			}
			std::cout <<std::endl;
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					C[i][j] += invM[i][k]*Ctmp[k][j];
				}
				
				std::cout<< "C[" <<i <<"][" <<j <<"] = " <<C[i][j] <<" ";
			}
			std::cout <<std::endl;
		}
	}

	LBD2Q9Mix::~LBD2Q9Mix(void)
	{
		delete[] phi;
		delete[] rho;
		delete[] U;
		delete[] omega;
	}

	void LBD2Q9Mix::init(void (*loader)(int x, int y, real* rho,
				real& ux, real& uy))  
	{
		#ifdef TEST_LB
		std::cout <<"at init ..." <<std::endl;
		#endif

		load_func = loader;

		for (int x = 0; x < NX; x++)
		{
			for (int y = 0; y < NY; y++)
			{
				real rho0[2], ux, uy;

				loader(x, y, rho0, ux, uy);

				// Store the macroscopic quatities
      				const real p = rho0[0];
      				const real r = rho0[1];

				phi[pos_r(x,y)] = p;
				rho[pos_r(x,y)] = r;
	
				U[pos_v(x,y) + 0] = ux;
				U[pos_v(x,y) + 1] = uy;
	    
      				//Init PDF.
      				//For Phi     
      				f_[0][pos_f(x,y)] = (1./24.)*p; 
      				f_[1][pos_f(x,y)] = (1./24.)*p;
      				f_[2][pos_f(x,y)] = (1./24.)*p;
      				f_[3][pos_f(x,y)] = (1./24.)*p;
	
      				f_[4][pos_f(x,y)] = (1./24.)*p;
      				f_[5][pos_f(x,y)] = (1./24.)*p;
      				f_[6][pos_f(x,y)] = (1./24.)*p;
      				f_[7][pos_f(x,y)] = (1./24.)*p;

     				f_[8][pos_f(x,y)] = (2./3.)*p;

      				//For Rho     
      				f_[0][pos_f(x,y) + 1] = (1./24.)*r; 
      				f_[1][pos_f(x,y) + 1] = (1./24.)*r;
      				f_[2][pos_f(x,y) + 1] = (1./24.)*r;
      				f_[3][pos_f(x,y) + 1] = (1./24.)*r;
	
      				f_[4][pos_f(x,y) + 1] = (1./24.)*r;
      				f_[5][pos_f(x,y) + 1] = (1./24.)*r;
      				f_[6][pos_f(x,y) + 1] = (1./24.)*r;
      				f_[7][pos_f(x,y) + 1] = (1./24.)*r;

     				f_[8][pos_f(x,y) + 1] = (2./3.)*r;

				#ifdef TEST_LB
				std::cout <<"(phi, rho)[" <<x <<"][" <<y <<"] = (" <<rho0[0] <<", " <<rho0[1] <<")\tU = [" <<ux <<", " <<uy <<"]" << std::endl;
				#endif
			}	
		}

	}

	void LBD2Q9Mix::f_eq(const int x, const int y, real f_out[9][2])
	{
		const real a = -0.1f, b = 0.1f, kappa = 0.09f; 

    		//Periodic BC. 
    		const int xm  = (x+NX-1)%NX;
    		const int xp  = (x+1)%NX;
		const int ym  = (y+NY-1)%(NY);
      		const int yp  = (y+1)%(NY);		
		
		const real p = phi[pos_r(x,y)];

		const real r = rho[pos_r(x,y)];
		const real UX = U[pos_v(x,y) + 0];
		const real UY = U[pos_v(x,y) + 1];

		const int O = pos_r(x, y); //Here

		const int N = pos_r(x,yp); //North	
		const int S = pos_r(x,ym); //South
		const int E = pos_r(xp,y); //East
		const int W = pos_r(xm,y); //West

		const int NE = pos_r(xp,yp); //North-East
		const int NW = pos_r(xm,yp); //North-West
		const int SW = pos_r(xm,ym); //South-West
		const int SE = pos_r(xp,ym); //South-East

      		//Compute Gradient
      		//const real dxp = (1./2.)*(phi[E]-phi[W]);
      		//const real dyp = (1./2.)*(phi[N]-phi[S]);
      		const real dxp = (1./12.)*( -phi[SW]+phi[NE]-phi[NW]+phi[SE] +4.*(phi[E]-phi[W]) );
      		const real dyp = (1./12.)*( -phi[SW]+phi[NE]+phi[NW]-phi[SE] +4.*(phi[N]-phi[S]) );

      		//Compute Lapacian
      		//const real ddp = phi[S]+phi[N]+phi[E]+phi[W]-4.*phi[O];   
      		const real ddp = (1./6.)*( phi[SW]+phi[NE]+phi[NW]+phi[SE] +4.*(phi[S]+phi[N]+phi[W]+phi[E] -5.*phi[O]) );

      		//Compute Pressure Tensor
      		const real pI  = 0.5*a*p*p + 0.75*b*p*p*p*p - kappa*( p*ddp + 0.5*(dxp*dxp + dyp*dyp) ) + r/3.;
      
      		const real Pxx = pI + kappa*dxp*dxp;
      		const real Pyy = pI + kappa*dyp*dyp;
      		const real Pxy =      kappa*dxp*dyp;

      		//Compute Chemical Potential
      		const real MU = r * ( a*p + b*p*p*p - kappa*ddp );

		// Compute the Eqilibrium pdf
		real ux, uy, uxx, uyy, uxy, usq;

		// Feq for phi
		ux = UX; 
		uy = UY;

      		uxx = p*ux*ux + MU;
      		uyy = p*uy*uy + MU;
      		uxy = 2.*p*ux*uy;
      		usq = uxx + uyy;

      		ux *= p;
      		uy *= p;

      		f_out[8][0] = fourOnine*((9./4.)*p -1.5*usq);

      		f_out[0][0] = oneOnine*( +3.*ux +4.5*uxx -1.5*usq); 
      		f_out[2][0] = oneOnine*( -3.*ux +4.5*uxx -1.5*usq); 
      		f_out[1][0] = oneOnine*( +3.*uy +4.5*uyy -1.5*usq); 
      		f_out[3][0] = oneOnine*( -3.*uy +4.5*uyy -1.5*usq); 

      		f_out[4][0] = oneOthirtysix*( +3.*(ux+uy)  +4.5*(uxx+uxy+uyy) -1.5*usq);
      		f_out[5][0] = oneOthirtysix*( +3.*(-ux+uy) +4.5*(uxx-uxy+uyy) -1.5*usq); 
      		f_out[6][0] = oneOthirtysix*( +3.*(-ux-uy) +4.5*(uxx+uxy+uyy) -1.5*usq);
      		f_out[7][0] = oneOthirtysix*( +3.*(ux-uy)  +4.5*(uxx-uxy+uyy) -1.5*usq);
   
		// Again for rho
      		ux = UX; 
		uy = UY;

      		uxx = r*ux*ux + Pxx;
      		uyy = r*uy*uy + Pyy;
      		uxy = 2.*r*ux*uy + 2.*Pxy;
      		usq = uxx + uyy; 

      		ux *= r;
      		uy *= r;

      		f_out[8][1] = fourOnine*((9./4.)*r -1.5*usq);

      		f_out[0][1] = oneOnine*( +3.*ux +4.5*uxx -1.5*usq); 
      		f_out[2][1] = oneOnine*( -3.*ux +4.5*uxx -1.5*usq); 
      		f_out[1][1] = oneOnine*( +3.*uy +4.5*uyy -1.5*usq); 
      		f_out[3][1] = oneOnine*( -3.*uy +4.5*uyy -1.5*usq); 

      		f_out[4][1] = oneOthirtysix*( +3.*(ux+uy)  +4.5*(uxx+uxy+uyy) -1.5*usq);
      		f_out[5][1] = oneOthirtysix*( +3.*(-ux+uy) +4.5*(uxx-uxy+uyy) -1.5*usq); 
      		f_out[6][1] = oneOthirtysix*( +3.*(-ux-uy) +4.5*(uxx+uxy+uyy) -1.5*usq);
      		f_out[7][1] = oneOthirtysix*( +3.*(ux-uy)  +4.5*(uxx-uxy+uyy) -1.5*usq);

		// For testing
		#ifdef TEST_LB
		//std::cout << "(phi, rho) = (" << p << ", " << r << ")\tU = [" << UX << ", " << UY << "]" << std::endl;
		#endif
	}

	void LBD2Q9Mix::computeMoments(void)
	{
 
		for (int x = 0; x < NX; x++)
		{
			for (int y = 0; y < NY; y++)
			{
				const int m = pos_f(x,y);
				const int n = pos_f(x,y) + 1;

      				const real phi_ = f_[0][m]+f_[1][m]+f_[2][m]+f_[3][m]+f_[4][m]+f_[5][m]+f_[6][m]+f_[7][m]+f_[8][m];
      
      				const real rho_ = f_[0][n]+f_[1][n]+f_[2][n]+f_[3][n]+f_[4][n]+f_[5][n]+f_[6][n]+f_[7][n]+f_[8][n];
     				const real ux_  = (f_[0][n]-f_[2][n]+f_[4][n]-f_[6][n]+f_[7][n]-f_[5][n])/rho_;
      				const real uy_  = (f_[1][n]-f_[3][n]+f_[4][n]-f_[6][n]+f_[5][n]-f_[7][n])/rho_;

				// Store the macroscopic quatities
				phi[pos_r(x,y)] = phi_;
				rho[pos_r(x,y)] = rho_;
	
				U[pos_v(x,y) + 0] = ux_;
				U[pos_v(x,y) + 1] = uy_;

				#ifdef TEST_LB
				std::cout <<"(phi, rho)[" <<x <<"][" <<y <<"] = (" <<phi_ <<", " <<rho_ <<")\tU = [" <<ux_ <<", " <<uy_ <<"]" << std::endl;
				#endif
			}
		}
	}
	
	void LBD2Q9Mix::collide(void)
	{
		real Feq[9][2];	
		
		for (int x = 0; x < NX; x++)
		{
			for (int y = 0; y < NY; y++)
			{
				f_eq(x, y, Feq);

				for (int l = 0; l < NVEL; l++)
				{
					for (int k = 0; k < RANK; k++)
					{
						f_[l][pos_f(x,y) + k] += omega[k] * (Feq[l][k] - f_[l][pos_f(x,y) + k]);
					}

					#ifdef TEST_LB
					//std::cout << "Feq[" << l << "][*]" << " = " << Feq[l][0] << ", " << Feq[l][1] << std::endl;
					#endif
				}
			}
		}
	}

	void LBD2Q9Mix::multcollide(void)
	{
		real Feq[9][2];	
		
		for (int x = 0; x < NX; x++)
		{
			for (int y = 0; y < NY; y++)
			{
				f_eq(x, y, Feq);

				for (int l = 0; l < NVEL; l++)
				{
					real tmp = 0;

					for (int k = 0; k < 9; k++)
					{
						tmp += C[l][k] * (Feq[k][0] - f_[k][pos_f(x,y)]);
					}

					f_[l][pos_f(x,y)] -= tmp;

					//f_[l][pos_f(x,y)]   += omega[0] * (Feq[l][0] - f_[l][pos_f(x,y)]  );
					f_[l][pos_f(x,y)+1] += omega[1] * (Feq[l][1] - f_[l][pos_f(x,y)+1]);

					#ifdef TEST_LB
					//std::cout << "Feq[" << l << "][*]" << " = " << Feq[l][0] << ", " << Feq[l][1] << std::endl;
					#endif
				}
			}
		}
	}
	
	void LBD2Q9Mix::step(void)
	{
		computeMoments();
		collide();
		//multcollide();
		stream();
		
		#ifdef TEST_LB
		std::cout << "take step " << " ..." << std::endl;
		#endif
	}

#ifdef USE_GRAPHICS
	void LBD2Q9Mix::reinit(void)
	{
		init(load_func);
	}

	void LBD2Q9Mix::initGUI(void)
	{
		mXdim = NX;
		mYdim = NY;

		mPause = 1;
      		mSingleStep = 0;
		mQuit = 0;
      		
		mRepeat = 100;
		mIterations = mRepeat;

		char phi_s[] = "phi";
		char rho_s[] = "rho";
		char U_s[] = "U";
		
		DefineGraphNxN_R(phi_s, phi, &mYdim, &mXdim, NULL);		
		DefineGraphNxN_R(rho_s, rho, &mYdim, &mXdim, NULL);  	
		DefineGraphNxN_RxR("U_s", U, &mYdim, &mXdim, NULL);  		
  		NewGraph();

		char Title_s[] = "Binary Fluid Lattice-Boltzmann Simulation";

		StartMenu(Title_s, 1); 

			char Visual_s[] = "Graphics Window";

  			SetActiveGraph(0);
  			DefineGraph(contour2d_, Visual_s);

  			/*StartMenu("Main Inputs",0);
  				DefineDouble("phi_zero",&r_zero[0]);
  				DefineDouble("rho_zero",&r_zero[1]);
  				DefineDouble("Amp",&Amp1);
  				DefineDouble("a",&a_);
  				DefineDouble("b",&b_);
  				DefineDouble("kappa",&kappa_);
  				DefineDouble("Nu2",&Nu2);
  				DefineDouble("tau0",&tau0);
  				DefineDouble("tau1",&tau1);
  				DefineDouble("UX_tp",&UX1);
  				DefineDouble("UY_tp",&UY1);
  			EndMenu();*/

  			/*StartMenu("Secondary Inputs",0);
  				DefineInt("xdim", &xdim);
  				DefineInt("ydim", &ydim);
  			EndMenu();*/

  			/*StartMenu("Stability Factors",0);
  				DefineDouble("s",&s);
  			EndMenu();*/

			char Controls_s[] = "Controls";
			char Iterations_s[] = "Iterations";
			char Repeat_s[] = "Repeat";

  			StartMenu(Controls_s, 0);
  				DefineInt(Iterations_s, &mIterations);
  				DefineInt(Repeat_s, &mRepeat);
  				//DefineInt("stabilize", &stabilize);
  			EndMenu();

  			/*StartMenu("Set Initializations",0);
  				DefineBool("Use Set Init", &setinit);
  				DefineInt("Num Vert Domains", &initvert);
  			EndMenu();
			*/ 		
		
			char Pause_s[] = "Puase";
			char SingleStep_s[] = "Single Step";
			char Quit_s[] = "Quit";
			char Reinit_s[] = "Reset";

  			DefineBool(Pause_s, &mPause);
  			DefineBool(SingleStep_s, &mSingleStep);
			//DefineFunction(Reinit_s, &reinit);
  			DefineBool(Quit_s, &mQuit);
	
  		EndMenu();
	}

	int LBD2Q9Mix::run(int argc, char **argv)
	{
		LBViewer lbv(NX,NY);
		lbv.setData(this, phi, rho, U);

		mglGraphFLTK gr;
		gr.Window(argc, argv, &lbv, "Binary Fluid Lattice-Boltzmann Simulation");

		return mglFlRun();
	}

	void LBD2Q9Mix::run(void)
	{
		int newData = 0;

		initGUI();

		while (!mQuit)
		{
      			Events(newData);
      			DrawGraphs();

    			if ( !mPause||mSingleStep ) 
			{
      				mSingleStep = 0;
      				newData = 1;
      
      				for (int n = 0; n < mRepeat; n++) 
				{
					mIterations++;

					step();
      				}

      				if (mRepeat == 0) 
					reinit();
    			}
    			else 
			{
      				//sleep(1);
			}
		}
	}
#endif

	void LBD2Q9Mix::run(int time)
	{
		for (int t = 0; t < time; t++)
		{
			#ifdef TEST_LB
			std::cout << "at time " << t << " ..." << std::endl;
			#endif

			step();
		}

		//#ifdef TEST_LB
		writeOutput();
		//#endif
	}

	void LBD2Q9Mix::writeOutput(void)
	{
		std::ofstream pfile, rfile;
		
		pfile.open("data_phi.txt");
		rfile.open("data_rho.txt");

	#ifdef USE_GRAPHICS
		mglGraphZB gr;
		gr.Alpha(false);
		gr.Light(true);
		gr.Light(0,mglPoint(1,0,-1));
	
		mglData dat(NX,NY);
		//dat.Modify("0.6*sin(2*pi*x)*sin(3*pi*y) + 0.4*cos(3*pi*(x*y))");
	#endif

  		for (int x = 0; x < NX; x++)
		{
    			for (int y = 0; y < NY; y++)
			{
      				pfile << phi[pos_r(x,y)] << "\t";
				rfile << rho[pos_r(x,y)] << "\t";

			#ifdef USE_GRAPHICS
				dat.a[pos_r(x,y)] = phi[pos_r(x,y)];
			#endif

				#ifdef TEST_LB
				std::cout <<"writeOutput: (phi, rho)[" <<x <<"][" <<y <<"] = (" <<phi[pos_r(x,y)] <<", " <<rho[pos_r(x,y)] <<")" << std::endl;
				#endif

    			}
    			pfile << std::endl;
			rfile << std::endl;
  		}

		pfile.close();
		rfile.close();

	#ifdef USE_GRAPHICS
		gr.Box();
		gr.Dens(dat);
		gr.Colorbar();

		gr.WritePNG("image.png");
	#endif

	}

}

