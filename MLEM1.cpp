#include "header_MLEM.h"

using namespace std;
using namespace cv ;

void MLEM::init()
{
	num_iter = 0;
	stop_enable = false ;
	invalid_input = false ;
}

void MLEM::set_iterations(int number)
{
	num_iter = number ;

	if (number<1)
			{cout<< "not a valid input" << endl ;
			invalid_input = true ;
			}

	if (number >= 1000)
		cout<< "too many no. of iterations, consider revising" << endl ;
}

void MLEM::set_init_image(Mat image)
{
	init_im = image.clone() ;

	if (0)
		{cout<< "null object cannot be initial starting point for MLEM" , "send a valid input";
		invalid_input = true ;
		}

	if(image.channels() != 1)
		{cout<<"invalid input, works only for 1-D image"<<endl ;
		invalid_input = true ;
		}
}

void MLEM::set_original(Mat image)
{
	original = image.clone() ;
	if (0)
		{cout<< "null object cannot be original image for MLEM"<<endl <<"send a valid input";
		invalid_input = true ;
		}
	if(image.channels() != 1)
	{cout<<"invalid input, works only for 1-D image"<<endl ;
	 invalid_input = true ;
	}
}

void MLEM::set_stop_enable(bool var)
{
	stop_enable = var ;
}

void MLEM::test_data(Mat proj, Mat sys_mat)
{
	int rows1 = sys_mat.rows ;
	int rows2 = init_im.rows ;
	int cols1 = sys_mat.cols ;
	int rows3 = proj.rows ;

	if ( (rows1 != rows2) | ( cols1 != rows3) )
		{cout<< "invalid input dimensions  ,consider revising"<<endl ;
		invalid_input = true ;
		}
}


float MLEM::get_SNR()
{
	return SNR_final;
}

Mat MLEM::get_result()
{
	return update_im ;
}

Mat MLEM::reconstruction(Mat noisy_proj ,Mat sys_mat)
{
	sys_mat = sys_mat.clone();
	noisy_proj = noisy_proj.clone();

	test_data(noisy_proj , sys_mat) ;

	if (invalid_input)
		{cout<< "cannot start reconstruction , invalid inputs"<<endl ;
		//return null image and end here
		}

	int i ;
	float snr_new, snr_old = 0 ;
	Mat calc_proj, err_proj ;

	update_im = init_im.clone() ;
	//Scalar var = sum(sys_mat) ; sum along rows only
	float var = .5;

	for (i = 1; i<num_iter; i++)
	{
		calc_proj = sys_mat.t() * update_im ;
		divide(noisy_proj, calc_proj,err_proj) ;
		err_proj = err_proj / var ;
		update_im = sys_mat*err_proj ;

		if (stop_enable == true)
			{
			snr_new = SNR(original , update_im ) ;

			 if (snr_new <= snr_old + .01)
			 {  SNR_final = snr_new ;
				break;
			 }
			 else snr_old = snr_new ;
			 SNR_final = snr_new ;
		    }


	}
	SNR_final = snr_new ;
	return update_im ;
}

float MLEM::SNR( Mat signal , Mat noisy_sig)
{
	Mat noise = signal.clone();
	Mat signal2 = signal.clone();
	Mat noise2 = noise.clone();

	absdiff(signal,noisy_sig , noise) ;
	multiply(signal,signal,signal2);
	multiply(noise, noise, noise2);

	Scalar var1 = sum(signal2);
	float signal_power = var1(0) / (signal2.rows * signal2.cols);

	Scalar var2 = ( sum(noise) );
	float noise_power = var2(0) / (noise.rows * noise.cols);

	float snr_power = .3010 * 10*log( ((signal_power+.1) / (noise_power+.1) ) );
    cout<<"snr   "<<snr_power<<endl ;

    return snr_power ;
}

