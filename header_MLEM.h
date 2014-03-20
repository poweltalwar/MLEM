#include <iostream>
#include<opencv2/core/core.hpp>

using namespace cv ;

class MLEM
{
/* num_iter     -- number of iterations for MLEM algorithm to run
 * SNR_final    -- final SNR of image reconstructed using MLEM reconstruction
 * stop_enable  -- whether we want to stop reconstruction at the point of maximum snr or complete the iteartions
 * invalid_input-- is set to true if any of the input is invalid
 * update_im    -- updated image at the end of each iteration
 * init_im      -- initialised image sent to the algo by user , set to null by default
 * original     -- original image , used for reference and snr calculation
 *
 * test data()  -- checks dimensions of input data
 * SNR()        -- calculates snr for reconstructed image
 *
 * init()             -- initialises the parameters
 * set_init_image()   -- sets initial image for reconstruction
 * set_original()     -- sets the original image
 * set_iterations()   -- sets the number of iterations
 * set_stop_enable()  -- sets control for stopping reconstruction at maximum SNR value
 * get_SNR()          -- gives final SNR of image
 * get_result()       -- gives out final reconstructed image
 * reconstruction()   -- performs reconstruction process , input projections and system matrix
 */
private :
	int   num_iter ;
	float SNR_final ;
	bool  stop_enable , invalid_input;
	Mat   update_im ,init_im, original;

	void  test_data(Mat , Mat);
	float SNR(Mat  ,Mat);


public:
	void init();
	void set_init_image(Mat);
	void set_original(Mat);
	void set_iterations(int);
	void set_stop_enable(bool);
	float get_SNR();
	Mat get_result();
	Mat reconstruction(Mat, Mat) ;
};
