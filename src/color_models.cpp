#include"color_models/color_models.h"

void RGB_2_sRGB(cv::Mat& img)
{
	double ThrLin2Gamma = 0.00304;
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				double temp = img.at<cv::Vec3f>(r, c)[channel] / 255.0;
				if (temp > ThrLin2Gamma)
				{
					img.at<cv::Vec3f>(r, c)[channel] = ((1 + 0.055) * pow(temp, 1 / 2.4) - 0.055) * 255;
				}
				else
				{
					img.at<cv::Vec3f>(r, c)[channel] = 12.92 * temp * 255;
				}
			}
		}
	}
}


void K3_RGB_2_sRGB(cv::Mat& img, float maximum)
{
	double ThrLin2Gamma = 0.00304 * maximum / 255;
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				double temp = img.at<cv::Vec3f>(r, c)[channel] / maximum;
				if (temp > ThrLin2Gamma)
				{
					img.at<cv::Vec3f>(r, c)[channel] = ((1 + 0.055) * pow(temp, 1 / 2.4) - 0.055) * maximum;
				}
				else
				{
					img.at<cv::Vec3f>(r, c)[channel] = 12.92 * temp * maximum;
				}
			}
		}
	}
}


void sRGB_2_RGB(cv::Mat& img)
{
	double ThrLin2Gamma = 0.04045;
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				double temp = img.at<cv::Vec3f>(r, c)[channel] / 255.0;
				if (temp > ThrLin2Gamma)
				{
					img.at<cv::Vec3f>(r, c)[channel] = pow(((temp + 0.055) / 1.055), 2.4) * 255;
				}
				else
				{
					img.at<cv::Vec3f>(r, c)[channel] = temp / 12.92 * 255;
				}
			}
		}
	}
}

void xyY_2_sBGR(cv::Mat& img) {
	cv::Mat data_XYZ(img.rows, img.cols, CV_32FC3);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			data_XYZ.at<cv::Vec3f>(r, c)[1] = img.at<cv::Vec3f>(r, c)[2];//Y
			data_XYZ.at<cv::Vec3f>(r, c)[0] = img.at<cv::Vec3f>(r, c)[2] *
				img.at<cv::Vec3f>(r, c)[0] / img.at<cv::Vec3f>(r, c)[1];//X
			data_XYZ.at<cv::Vec3f>(r, c)[2] = img.at<cv::Vec3f>(r, c)[2] *
				(1 - img.at<cv::Vec3f>(r, c)[0] - img.at<cv::Vec3f>(r, c)[1])
				/ img.at<cv::Vec3f>(r, c)[1];//y
		}
	}

	cv::cvtColor(data_XYZ, img, cv::COLOR_XYZ2BGR);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				if (img.at<cv::Vec3f>(r, c)[channel] > 255)
					img.at<cv::Vec3f>(r, c)[channel] = 255;
				else if (img.at<cv::Vec3f>(r, c)[channel] < 0)
					img.at<cv::Vec3f>(r, c)[channel] = 0;

			}
		}
	}
}
void XYZ_2_BGR(cv::Mat& img)

{
	cv::Mat data_BGR(img.rows, img.cols, CV_32FC3);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			data_BGR.at<cv::Vec3f>(r, c)[0] = img.at<cv::Vec3f>(r, c)[0] * 0.055648 - img.at<cv::Vec3f>(r, c)[1] * 0.204043 + img.at<cv::Vec3f>(r, c)[2] * 1.057311;
			data_BGR.at<cv::Vec3f>(r, c)[1] = -img.at<cv::Vec3f>(r, c)[0] * 0.969256 + img.at<cv::Vec3f>(r, c)[1] * 1.875992 + img.at<cv::Vec3f>(r, c)[2] * 0.041556;
			data_BGR.at<cv::Vec3f>(r, c)[2] = img.at<cv::Vec3f>(r, c)[0] * 3.240479 - img.at<cv::Vec3f>(r, c)[1] * 1.53715 -img.at<cv::Vec3f>(r, c)[2] * 0.498535;
		}
	}
	data_BGR *= 2.55;
	img = data_BGR.clone();
}

void XYZ_2_sBGR(cv::Mat& img)
{
	cv::cvtColor(img, img, cv::COLOR_XYZ2BGR);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				if (img.at<cv::Vec3f>(r, c)[channel] > 255)
					img.at<cv::Vec3f>(r, c)[channel] = 255;
				else if (img.at<cv::Vec3f>(r, c)[channel] < 0)
					img.at<cv::Vec3f>(r, c)[channel] = 0;

			}
		}
	}
}

void Yxy_2_RGB(cv::Mat& img) {
	
	cv::Mat data_XYZ(img.rows, img.cols, CV_32FC3);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			data_XYZ.at<cv::Vec3f>(r, c)[1] = img.at<cv::Vec3f>(r, c)[2];//Y
			data_XYZ.at<cv::Vec3f>(r, c)[0] = img.at<cv::Vec3f>(r, c)[2] *
				img.at<cv::Vec3f>(r, c)[0] / img.at<cv::Vec3f>(r, c)[1];//X
			data_XYZ.at<cv::Vec3f>(r, c)[2] = img.at<cv::Vec3f>(r, c)[2] *
				(1 - img.at<cv::Vec3f>(r, c)[0] - img.at<cv::Vec3f>(r, c)[1])
				/ img.at<cv::Vec3f>(r, c)[1];//y
		}
	}
	cv::cvtColor(data_XYZ, img, cv::COLOR_XYZ2BGR);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				if (img.at<cv::Vec3f>(r, c)[channel] > 255)
					img.at<cv::Vec3f>(r, c)[channel] = 255;
				else if (img.at<cv::Vec3f>(r, c)[channel] < 0)
					img.at<cv::Vec3f>(r, c)[channel] = 0;

			}
		}
	}
}
void RGB_2_xyY(cv::Mat& img) {

	cv::Mat data_XYZ;
	cv::cvtColor(img, data_XYZ, cv::COLOR_BGR2XYZ);
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			double reg = data_XYZ.at<cv::Vec3f>(r, c)[0] + data_XYZ.at<cv::Vec3f>(r, c)[1] + data_XYZ.at<cv::Vec3f>(r, c)[2];
			img.at<cv::Vec3f>(r, c)[0] = data_XYZ.at<cv::Vec3f>(r, c)[0] / reg; //x
			img.at<cv::Vec3f>(r, c)[1] = data_XYZ.at<cv::Vec3f>(r, c)[1] / reg; //y
			img.at<cv::Vec3f>(r, c)[2] = data_XYZ.at<cv::Vec3f>(r, c)[1] * 100.0; //Y
		}
	}
}

void linearRGB2XYZ_img(cv::Mat& img)
{
	float RR, GG, BB;
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			BB = img.at<cv::Vec3f>(row, col)[0] / 255.0;
			GG = img.at<cv::Vec3f>(row, col)[1] / 255.0;
			RR = img.at<cv::Vec3f>(row, col)[2] / 255.0;

			img.at<cv::Vec3f>(row, col)[0] = 0.412453f * RR + 0.357580f * GG + 0.180423f * BB;
			img.at<cv::Vec3f>(row, col)[1] = 0.212671f * RR + 0.715160f * GG + 0.072169f * BB;
			img.at<cv::Vec3f>(row, col)[2] = 0.019334f * RR + 0.119193f * GG + 0.950227f * BB;

		}
	}
	img *= 100.0;
}


void linearRGB2XYZ(float R, float G, float B, float* X, float* Y, float* Z)
{
	float RR = R / 255.0;
	float GG = G / 255.0;
	float BB = B / 255.0;
	//*X = 0.4124564f * RR + 0.3575761f * GG + 0.1804375f * BB;
	//*Y = 0.2126729f * RR + 0.7151522f * GG + 0.0721750f * BB;
	//*Z = 0.0193339f * RR + 0.1191920f * GG + 0.9503041f * BB;
	*X = 0.412453f * RR + 0.357580f * GG + 0.180423f * BB;
	*Y = 0.212671f * RR + 0.715160f * GG + 0.072169f * BB;
	*Z = 0.019334f * RR + 0.119193f * GG + 0.950227f * BB;
}
void XYZ2Lab(float X, float Y, float Z, float* L, float* a, float* b)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = 0.950456f;
	const float Yn = 1.0f;
	const float Zn = 1.088754f;
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	X /= (Xn);
	Y /= (Yn);
	Z /= (Zn);
	if (Y > 0.008856f)
		fY = pow(Y, param_13);
	else
		fY = 7.787f * Y + param_16116;

	if (X > 0.008856f)
		fX = pow(X, param_13);
	else
		fX = 7.787f * X + param_16116;

	if (Z > 0.008856)
		fZ = pow(Z, param_13);
	else
		fZ = 7.787f * Z + param_16116;
	*L = 116.0f * fY - 16.0f;
	*L = *L > 0.0f ? *L : 0.0f;
	*a = 500.0f * (fX - fY);
	*b = 200.0f * (fY - fZ);
}

void Mat_XYZ2Lab(cv::Mat str, cv::Mat& out)
{
	cv::Mat temp;
	str.convertTo(temp, CV_32FC3);
	str = str / 100.0;
	out = str.clone();
	for (int y = 0; y < str.rows; y++)
	{
		for (int x = 0; x < str.cols; x++)
		{
			cv::Vec3f XYZ_temp;
			cv::Vec3f Lab;
			XYZ_temp = str.at<cv::Vec3f>(y, x);
			XYZ2Lab(XYZ_temp[0], XYZ_temp[1], XYZ_temp[2], &Lab[0], &Lab[1], &Lab[2]);
			out.at<cv::Vec3f>(y, x) = Lab;
		}
	}
}


void XYZ2Lab_refWhite(cv::Vec3f inputXYZ, cv::Vec3f ReferenceWhiteXYZ, cv::Vec3f &OutputLab)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = ReferenceWhiteXYZ[0];
	const float Yn = ReferenceWhiteXYZ[1];
	const float Zn = ReferenceWhiteXYZ[2];
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	float X, Y, Z;
	X = inputXYZ[0]; Y = inputXYZ[1]; Z = inputXYZ[2];
	X /= (Xn);
	Y /= (Yn);
	Z /= (Zn);
	if (Y > 0.008856f)
		fY = pow(Y, param_13);
	else
		fY = 7.787f * Y + param_16116;

	if (X > 0.008856f)
		fX = pow(X, param_13);
	else
		fX = 7.787f * X + param_16116;

	if (Z > 0.008856)
		fZ = pow(Z, param_13);
	else
		fZ = 7.787f * Z + param_16116;
	OutputLab[0] = 116.0f * fY - 16.0f;
	OutputLab[0] = OutputLab[0] > 0.0f ? OutputLab[0] : 0.0f;
	OutputLab[1] = 500.0f * (fX - fY);
	OutputLab[2] = 200.0f * (fY - fZ);
}

void Mat_XYZ2Lab_RfWhite(cv::Mat str, cv::Vec3f ReferenceWhiteXYZ, cv::Mat& out)
{
	cv::Mat temp;
	str.convertTo(temp, CV_32FC3);
	out = str.clone();
	for (int y = 0; y < str.rows; y++)
	{
		for (int x = 0; x < str.cols; x++)
		{
			cv::Vec3f XYZ_temp;
			cv::Vec3f Lab;
			XYZ_temp = str.at<cv::Vec3f>(y, x);
			XYZ2Lab_refWhite(XYZ_temp, ReferenceWhiteXYZ, Lab);
			out.at<cv::Vec3f>(y, x) = Lab;
		}
	}
}

void Lab2XYZ_RfWhite(cv::Vec3f inputLab, cv::Vec3f ReferenceWhiteXYZ, cv::Vec3f& OutputXYZ)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = ReferenceWhiteXYZ[0];
	const float Yn = ReferenceWhiteXYZ[1];
	const float Zn = ReferenceWhiteXYZ[2];
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	float X, Y, Z;
	fY = (inputLab[0] + 16.0f) / 116.0;
	fX = inputLab[1] / 500.0f + fY;
	fZ = fY - inputLab[2] / 200.0f;
	if (powf(fY, 3.0) > 0.008856)
		Y = powf(fY, 3.0);
	else
		Y = (fY - param_16116) / 7.787f;

	if (powf(fX, 3) > 0.008856)
		X = fX * fX * fX;
	else
		X = (fX - param_16116) / 7.787f;

	if (powf(fZ, 3.0) > 0.008856)
		Z = fZ * fZ * fZ;
	else
		Z = (fZ - param_16116) / 7.787f;
	
	OutputXYZ[0] = X * Xn;
	OutputXYZ[1] = Y * Yn;
	OutputXYZ[2] = Z * Zn;
}


void Vec_Lab2XYZ_RfWhite(std::vector<std::vector<cv::Vec3f>>& input_Lab, cv::Vec3f ReferenceWhiteXYZ)
{
	cv::Mat temp;
	for (int Hue= 0; Hue < input_Lab.size(); Hue++)
	{
		for (int col = 0; col < input_Lab[Hue].size(); col++)
		{
			cv::Vec3f XYZ_temp;
			Lab2XYZ_RfWhite(input_Lab[Hue][col], ReferenceWhiteXYZ, XYZ_temp);
			input_Lab[Hue][col] = XYZ_temp;
		}
	}
}

void Vec_Lab2XYZ(std::vector<std::vector<cv::Vec3f>>& input_Lab)
{
	cv::Mat temp;
	for (int Hue = 0; Hue < input_Lab.size(); Hue++)
	{
		for (int col = 0; col < input_Lab[Hue].size(); col++)
		{
			cv::Vec3f XYZ_temp;
			Lab2XYZ(input_Lab[Hue][col][0], input_Lab[Hue][col][1], input_Lab[Hue][col][2], &XYZ_temp[0], &XYZ_temp[1], &XYZ_temp[2]);
			XYZ_temp *= 100;
			input_Lab[Hue][col] = XYZ_temp;
		}
	}
}

void XYZ2Lab_no_limit(float X, float Y, float Z, float* L, float* a, float* b)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = 0.950456f;
	const float Yn = 1.0f;
	const float Zn = 1.088754f;
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	X /= (Xn);
	Y /= (Yn);
	Z /= (Zn);
	if (Y > 0.008856f)
		fY = pow(Y, param_13);
	else
		fY = 7.787f * Y + param_16116;

	if (X > 0.008856f)
		fX = pow(X, param_13);
	else
		fX = 7.787f * X + param_16116;

	if (Z > 0.008856)
		fZ = pow(Z, param_13);
	else
		fZ = 7.787f * Z + param_16116;
	*L = 116.0f * fY - 16.0f;
	*a = 500.0f * (fX - fY);
	*b = 200.0f * (fY - fZ);
}

void XYZ2Lab_Could_negative(float X, float Y, float Z, float* L, float* a, float* b)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = 0.950456f;
	const float Yn = 1.0f;
	const float Zn = 1.088754f;
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	int nagX = 1, nagY = 1, nagZ = 1;
	if (X < 0)
	{
		X *= -1;
		nagX = -1;
	}
	if (Y < 0)
	{
		Y *= -1;
		nagY = -1;
	}
	if (Z < 0)
	{
		Z *= -1;
		nagZ = -1;
	}

	X /= (Xn);
	Y /= (Yn);
	Z /= (Zn);
	if (Y > 0.008856f)
		fY = pow(Y, param_13);
	else
		fY = 7.787f * Y + param_16116;

	if (X > 0.008856f)
		fX = pow(X, param_13);
	else
		fX = 7.787f * X + param_16116;

	if (Z > 0.008856)
		fZ = pow(Z, param_13);
	else
		fZ = 7.787f * Z + param_16116;
	
	*L = 116.0f * fY - 16.0f;
	*a = 500.0f * (fX - fY);
	*b = 200.0f * (fY - fZ);

	*L *= nagY;
	*a *= nagX;
	*b *= nagZ;
}

void XYZ2LinearLab(float X, float Y, float Z, float* L, float* a, float* b)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
	const float Xn = 0.950456f;
	const float Yn = 1.0f;
	const float Zn = 1.088754f;
	//const float Xn = 0.964212f;
	//const float Yn = 1.0f;
	//const float Zn = 0.825188f;
	float fX, fY, fZ;
	X /= (Xn);
	Y /= (Yn);
	Z /= (Zn);
	if (Y > 0.008856f)
		fY = Y;
	else
		fY = Y;

	if (X > 0.008856f)
		fX = X;
	else
		fX = X;

	if (Z > 0.008856)
		fZ = Z;
	else
		fZ = Z;
	*L = 116.0f * fY - 16.0f;
	*L = *L > 0.0f ? *L : 0.0f;
	*a = 500.0f * (fX - fY);
	*b = 200.0f * (fY - fZ);
}

void Linear2RGBLab(cv::Mat str, cv::Mat& out)
{
	cv::Mat temp;
	str.convertTo(temp, CV_32FC3, 255.0);
	out = str.clone();
	//out = str.clone();
	for (int y = 0; y < str.rows; y++)
	{
		for (int x = 0; x < str.cols; x++)
		{
			float X, Y, Z;
			float L, a, b;
			linearRGB2XYZ(temp.at<cv::Vec3f>(y, x)[2], temp.at<cv::Vec3f>(y, x)[1], temp.at<cv::Vec3f>(y, x)[0], &X, &Y, &Z);
			XYZ2Lab(X, Y, Z, &L, &a, &b);
			out.at<cv::Vec3f>(y, x)[0] = L;
			out.at<cv::Vec3f>(y, x)[1] = a;
			out.at<cv::Vec3f>(y, x)[2] = b;
		}
	}
}

void LinearRGB2LinearLab(cv::Mat str, cv::Mat& out)
{
	cv::Mat temp;
	str.convertTo(temp, CV_32FC3, 255.0);
	out = str.clone();
	//out = str.clone();
	for (int y = 0; y < str.rows; y++)
	{
		for (int x = 0; x < str.cols; x++)
		{
			float X, Y, Z;
			float L, a, b;
			linearRGB2XYZ(temp.at<cv::Vec3f>(y, x)[2], temp.at<cv::Vec3f>(y, x)[1], temp.at<cv::Vec3f>(y, x)[0], &X, &Y, &Z);
			XYZ2LinearLab(X, Y, Z, &L, &a, &b);
			out.at<cv::Vec3f>(y, x)[0] = L;
			out.at<cv::Vec3f>(y, x)[1] = a;
			out.at<cv::Vec3f>(y, x)[2] = b;
		}
	}
}

void XYZ2LinearsRGB(float X, float Y, float Z, float* R, float* G, float* B)
{
	float RR, GG, BB;
	RR = 3.2404542f * X - 1.5371385f * Y - 0.4985314f * Z;
	GG = -0.9692660f * X + 1.8760108f * Y + 0.0415560f * Z;
	BB = 0.0556434f * X - 0.2040259f * Y + 1.0572252f * Z;

	//RR = 3.1338561f * X - 1.6168667f * Y - 0.4906146f * Z;
	//GG = -0.9787684f * X + 1.9161415f * Y + 0.0334540f * Z;
	//BB = 0.0719453f * X - 0.2289914f * Y + 1.4052427f * Z;
	//RR = gamma_XYZ2RGB(RR);
	//GG = gamma_XYZ2RGB(GG);
	//BB = gamma_XYZ2RGB(BB);

	//RR = clip255(RR * 255.0 + 0.5);
	//GG = clip255(GG * 255.0 + 0.5);
	//BB = clip255(BB * 255.0 + 0.5);

	* R = RR;
	*G = GG;
	*B = BB;
}
void Lab2XYZ(float L, float a, float b, float* X, float* Y, float* Z)
{
	const float param_13 = 1.0f / 3.0f;
	const float param_16116 = 16.0f / 116.0f;
#ifdef D65
	const float Xn = 0.950456f;
	const float Yn = 1.0f;
	const float Zn = 1.088754f;
#else
	const float Xn = 0.964212f;
	const float Yn = 1.0f;
	const float Zn = 0.825188f;
#endif // D65
	float fX, fY, fZ;
	fY = (L + 16.0f) / 116.0;
	fX = a / 500.0f + fY;
	fZ = fY - b / 200.0f;

	if (powf(fY, 3.0) > 0.008856)
		*Y = powf(fY, 3.0);
	else
		*Y = (fY - param_16116) / 7.787f;

	if (powf(fX, 3) > 0.008856)
		*X = fX * fX * fX;
	else
		*X = (fX - param_16116) / 7.787f;

	if (powf(fZ, 3.0) > 0.008856)
		*Z = fZ * fZ * fZ;
	else
		*Z = (fZ - param_16116) / 7.787f;

	(*X) *= (Xn);
	(*Y) *= (Yn);
	(*Z) *= (Zn);
}
void Lab2LinearsRGB(cv::Mat& bmp_img, cv::Mat lab_img)
{
	float R, G, B;
	float X, Y, Z, L, a, b;

	bmp_img = lab_img.clone();
	for (int y = 0; y < bmp_img.rows; y++)
	{
		for (int x = 0; x < bmp_img.cols; x++)
		{
			L = lab_img.at<cv::Vec3f>(y, x)[0];
			a = lab_img.at<cv::Vec3f>(y, x)[1];
			b = lab_img.at<cv::Vec3f>(y, x)[2];

			Lab2XYZ(L, a, b, &X, &Y, &Z);
			XYZ2LinearsRGB(X, Y, Z, &R, &G, &B);

			bmp_img.at<cv::Vec3f>(y, x)[0] = B;
			bmp_img.at<cv::Vec3f>(y, x)[1] = G;
			bmp_img.at<cv::Vec3f>(y, x)[2] = R;
		}
	}
}

void Lab2LCH(cv::Mat img, cv::Mat& out)
{
	out = img.clone();
	out.convertTo(out, CV_32FC3);
	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < out.cols; col++)
		{
			double var_H = fmod(atan2(out.at<cv::Vec3f>(row,col)[2], out.at<cv::Vec3f>(row, col)[1]) , 360.0);//Quadrant by signs

			if (var_H > 0)
				var_H = (var_H / CV_PI) * 180;
			else
				var_H = 360 - (abs(var_H) / CV_PI) * 180;

			if (var_H == 360.0)
				var_H = 0;
			out.at<cv::Vec3f>(row, col)[0] = out.at<cv::Vec3f>(row, col)[0];
			out.at<cv::Vec3f>(row, col)[1] = sqrt(out.at<cv::Vec3f>(row, col)[1] * out.at<cv::Vec3f>(row, col)[1] + out.at<cv::Vec3f>(row, col)[2] * out.at<cv::Vec3f>(row, col)[2]);
			out.at<cv::Vec3f>(row, col)[2] = var_H;
		}
	}
}

void LCH2Lab(cv::Mat img, cv::Mat& out)
{
	out = img.clone();
	out.convertTo(out, CV_32FC3);
	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < out.cols; col++)
		{
			out.at<cv::Vec3f>(row, col)[0] = out.at<cv::Vec3f>(row, col)[0];
			out.at<cv::Vec3f>(row, col)[1] = cos(img.at<cv::Vec3f>(row, col)[2] * CV_PI / 180) * img.at<cv::Vec3f>(row, col)[1];
			out.at<cv::Vec3f>(row, col)[2] = sin(img.at<cv::Vec3f>(row, col)[2] * CV_PI / 180) * img.at<cv::Vec3f>(row, col)[1];
		}
	}
}

void XYZ_normalize_refW(cv::Mat img, cv::Mat &out, cv::Vec3f White_point)
{
	img = out.clone();
	out.convertTo(out, CV_32FC3);

	const float Xn = 95.0456f;
	const float Yn = 100.0f;
	const float Zn = 108.8754f;
	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			out.at<cv::Vec3f>(row, col)[0] = out.at<cv::Vec3f>(row, col)[0] / White_point[0] * Xn;
			out.at<cv::Vec3f>(row, col)[1] = out.at<cv::Vec3f>(row, col)[1] / White_point[1] * Yn;
			out.at<cv::Vec3f>(row, col)[2] = out.at<cv::Vec3f>(row, col)[2] / White_point[2] * Zn;
		}
	}
}

//from https://bottosson.github.io/posts/oklab
void XYZ2OkLab(cv::Mat img,cv::Mat& out)
{
	//XYZ img's range is depends on Y with 0 to 100(D65)
	out = img.clone();
	out.convertTo(out, CV_32FC3);
	out /= 100.0;
	double X, Y, Z;
	double l, m, s;

	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < out.cols; col++)
		{
			X = out.at<cv::Vec3f>(row, col)[0];
			Y = out.at<cv::Vec3f>(row, col)[1];
			Z = out.at<cv::Vec3f>(row, col)[2];

			l = X * 0.8189330101f + Y * 0.3618667424f - Z * 0.1288597137f;
			m = X * 0.0329845436f + Y * 0.9293118715f + Z * 0.0361456387f;
			s = X * 0.0482003018f + Y * 0.2643662691f + Z * 0.6338517070f;

			l = pow(l, 1.0 / 3);
			m = pow(m, 1.0 / 3);
			s = pow(s, 1.0 / 3);


			out.at<cv::Vec3f>(row, col)[0] = (l * 0.210454255f + m * 0.7936177850f - s * 0.0040720468f) * 100;
			out.at<cv::Vec3f>(row, col)[1] = (l * 1.9779984951f - m * 2.4285922050f + s * 0.4505937099f) * 100;
			out.at<cv::Vec3f>(row, col)[2] = (l * 0.0259040371f + m * 0.7827717662f - s * 0.8086757660f) * 100;
		}
	}
}

void LinearsRGB2OkLab(cv::Mat img, cv::Mat& out)
{
	//RGB img's range is 0~255
	out = img.clone();
	out.convertTo(out, CV_32FC3);
	out /= 255.0;
	double B, G, R;
	double l, m, s;

	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < out.cols; col++)
		{
			B = out.at<cv::Vec3f>(row, col)[0];
			G = out.at<cv::Vec3f>(row, col)[1];
			R = out.at<cv::Vec3f>(row, col)[2];

			l = R * 0.4122214708f + G * 0.5363325363f + B * 0.0514459929f;
			m = R * 0.2119034982f + G * 0.6806995451f + B * 0.1073969566f;
			s = R * 0.0883024619f + G * 0.2817188376f + B * 0.6299787005f;

			l = pow(l, 1.0 / 3);
			m = pow(m, 1.0 / 3);
			s = pow(s, 1.0 / 3);


			out.at<cv::Vec3f>(row, col)[0] = (l * 0.210454255f + m * 0.7936177850f - s * 0.0040720468f) * 100;
			out.at<cv::Vec3f>(row, col)[1] = (l * 1.9779984951f - m * 2.4285922050f + s * 0.4505937099f) * 100;
			out.at<cv::Vec3f>(row, col)[2] = (l * 0.0259040371f + m * 0.7827717662f - s * 0.8086757660f) * 100;
		}
	}
}

void OkLab2LinearRGB(cv::Mat img,cv::Mat &out)
{
	//Lab range is L(0~100)
	out = img.clone();
	out.convertTo(out, CV_32FC3);
	out /= 100.0;
	double L, a, b;
	double l, m, s;

	for (int row = 0; row < out.rows; row++)
	{
		for (int col = 0; col < out.cols; col++)
		{
			L = out.at<cv::Vec3f>(row, col)[0];
			a = out.at<cv::Vec3f>(row, col)[1];
			b = out.at<cv::Vec3f>(row, col)[2];

			l = L + a * 0.3963377774f + b * 0.2158037573f;
			m = L - a * 0.1055613458f - b * 0.0638541728f;
			s = L - a * 0.0894841775f - b * 1.2914855480f;

			l = l * l * l;
			m = m * m * m;
			s = s * s * s;


			out.at<cv::Vec3f>(row, col)[2] = (l * 4.0767416621f - m * 3.3077115913f + s * 0.2309699292f) * 255;
			out.at<cv::Vec3f>(row, col)[1] = (-l * 1.2684380046f + m * 2.6097574011f - s * 0.3413193965f) * 255;
			out.at<cv::Vec3f>(row, col)[0] = (-l * 0.0041960863f - m * 0.7034186147f + s * 1.7076147010f) * 255;
		}
	}
}

void OkLab2XYZ(cv::Vec3f Lab, cv::Vec3f &XYZ)
{
	cv::Mat M1 = (cv::Mat_ <float>(3, 3) << 0.8189330101f, 0.3618667424f, -0.1288597137f, 
											0.0329845436f, 0.9293118715f, 0.0361456387f, 
											0.0482003018f, 0.2643662691f, 0.6338517070);

	cv::Mat M2 = (cv::Mat_ <float>(3, 3) << 0.2104542553f, 0.7936177850f, -0.0040720468f,
											1.9779984951f, -2.4285922050f, 0.4505937099f,
											0.0259040371f, 0.7827717662f, -0.8086757660f);

	double L, a, b;
	double l, m, s;

	cv::Mat Lab_temp = (cv::Mat_<float>(3, 1) << Lab[0], Lab[1], Lab[2]);
	cv::Mat XYZ_temp(3, 1, CV_32FC1);

	cv::Mat lms = M2.inv() * Lab_temp;

	l = lms.at<float>(0, 0);
	m = lms.at<float>(1, 0);
	s = lms.at<float>(2, 0);

	lms.at<float>(0, 0) = l * l * l;
	lms.at<float>(1, 0) = m * m * m;
	lms.at<float>(2, 0) = s * s * s;

	XYZ_temp = M1.inv() * lms;

	XYZ[0] = XYZ_temp.at<float>(0, 0);
	XYZ[1] = XYZ_temp.at<float>(1, 0);
	XYZ[2] = XYZ_temp.at<float>(2, 0);
}

void Vec_OkLab2XYZ(std::vector<std::vector<cv::Vec3f>>& input_OkLab)
{
	cv::Vec3f XYZ_temp, Lab_temp;
	for (int Hue = 0; Hue < input_OkLab.size(); Hue++)
	{
		for (int col = 0; col < input_OkLab[Hue].size(); col++)
		{
			Lab_temp = input_OkLab[Hue][col] / 100;
			OkLab2XYZ(Lab_temp, XYZ_temp);
			XYZ_temp *= 100;
			input_OkLab[Hue][col] = XYZ_temp;
		}
	}
}

void XYZ2OkLab_Vec(cv::Vec3f img, cv::Vec3f& out)
{
	//XYZ img's range is depends on Y with 0 to 100(D65)
	img /= 100.0;
	double X, Y, Z;
	double l, m, s;

	X = img[0];
	Y = img[1];
	Z = img[2];

	l = X * 0.8189330101f + Y * 0.3618667424f - Z * 0.1288597137f;
	m = X * 0.0329845436f + Y * 0.9293118715f + Z * 0.0361456387f;
	s = X * 0.0482003018f + Y * 0.2643662691f + Z * 0.6338517070f;

	l = pow(l, 1.0 / 3);
	m = pow(m, 1.0 / 3);
	s = pow(s, 1.0 / 3);

	out[0] = (l * 0.210454255f + m * 0.7936177850f - s * 0.0040720468f) * 100.0;
	out[1] = (l * 1.9779984951f - m * 2.4285922050f + s * 0.4505937099f) * 100.0;
	out[2] = (l * 0.0259040371f + m * 0.7827717662f - s * 0.8086757660f) * 100.0;
}


double CIEdeltaE2000(cv::Vec3f color_Lab1, cv::Vec3f color_Lab2)
{
	double L1 = color_Lab1[0];
	double L2 = color_Lab2[0];
	double a1 = color_Lab1[1];
	double a2 = color_Lab2[1];
	double b1 = color_Lab1[2];
	double b2 = color_Lab2[2];
	double L_diff = L2 - L1;
	double L_bar = (L1 + L2) / 2;
	double C1 = sqrt(a1 * a1 + b1 * b1);
	double C2 = sqrt(a2 * a2 + b2 * b2);
	double C_bar = (C1 + C2) / 2;
	double G = 1 - sqrt(pow(C_bar, 7) / (pow(C_bar, 7) + pow(25, 7)));
	double a1_prime = a1 + G * a1 / 2;
	double a2_prime = a2 + G * a2 / 2;
	double C1_prime = sqrt(a1_prime * a1_prime + b1 * b1);
	double C2_prime = sqrt(a2_prime * a2_prime + b2 * b2);
	double C_bar_prime = (C1_prime + C2_prime) / 2;
	double C_diff = C2_prime - C1_prime;
	double h1_prime = atan2(b1, a1_prime);
	double h2_prime = atan2(b2, a2_prime);


	if (h1_prime > 0)
		h1_prime = (h1_prime / CV_PI) * 180;
	else
		h1_prime = 360 - (abs(h1_prime) / CV_PI) * 180;

	if (h1_prime == 360.0)
		h1_prime = 0;

	if (h2_prime > 0)
		h2_prime = (h2_prime / CV_PI) * 180;
	else
		h2_prime = 360 - (abs(h2_prime) / CV_PI) * 180;

	if (h2_prime == 360.0)
		h2_prime = 0;


	double h_prime_diff;
	if (abs(h1_prime - h2_prime) <= 180)
	{
		h_prime_diff = h2_prime - h1_prime;
	}
	else if (abs(h1_prime - h2_prime) > 180 && h2_prime <= h1_prime)
	{
		h_prime_diff = h2_prime - h1_prime + 360;
	}
	else if (abs(h1_prime - h2_prime) > 180 && h2_prime > h1_prime)
	{
		h_prime_diff = h2_prime - h1_prime - 360;
	}
	double H_prime_diff = 2 * sqrt(C1_prime * C2_prime) * sin(h_prime_diff * radian / 2);
	double H__bar_prime;
	if (abs(h1_prime - h2_prime) > 180)
	{
		H__bar_prime = (h1_prime + h2_prime + 360) / 2;
	}
	else
	{
		H__bar_prime = (h1_prime + h2_prime) / 2;
	}

	double T = 1 - 0.17 * cos((H__bar_prime - 30) * radian) + 0.24 * cos(2 * H__bar_prime * radian)
		+ 0.32 * cos((3 * H__bar_prime + 6) * radian) - 0.2 * cos((4 * H__bar_prime - 63) * radian);
	std::cout << "h1_prime" << h1_prime << "\n";
	std::cout << "h2_prime" << h2_prime << "\n";
	double S_L = 1 + 0.015 * pow((L_bar - 50), 2) / sqrt(20 + pow((L_bar - 50), 2));
	double S_C = 1 + 0.045 * C_bar_prime;
	double S_H = 1 + 0.015 * C_bar_prime * T;
	double R_T = -2 * sqrt(pow(C_bar_prime, 7) / (pow(C_bar_prime, 7) + pow(25, 7))) * sin(60 * exp(-pow((H__bar_prime - 275) / 25, 2)) * radian);
	double deltaE = sqrt(pow(L_diff / S_L, 2) + pow(C_diff / S_C, 2) + pow(H_prime_diff / S_H, 2) + R_T * C_diff * H_prime_diff / S_C / S_H);

	return deltaE;
}

