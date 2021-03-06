#pragma once

#include <opencv2/opencv.hpp>
#include <iomanip>
#include "StageCoding.h"
#include "golomb.h"
#include "file.h"

namespace VideoCoding
{
	using std::cin; using std::cout; using std::endl;
	using namespace cv;
	class FourthVideoEnc : public virtual StageCoding
	{
		public:
			FourthVideoEnc(string ifname, string ofname, char mode, uint predictMode=6, uint blockSize=8, uint searchArea=4, uint periodicity=15, char thresholdMode='r', double t=1., double base_threshold=12., double ceil_threshold=4., double min_threshold=40., char searchMode='s', double Kb=0.114, double Kr=0.299);
			~FourthVideoEnc();

			Mat encode(Mat* frame, uint fps = 0);
			bool decode(Mat* frame);
			void encodeEnded();
			uint getFPS();
		private:
			void BGR2YCrCb(Mat* frame);
			void YCrCb2BGR(Mat* frame);
			void writeHeader(Mat* frame, uint fps);
			void save();
			double calcThreshold(Mat a, Mat b);
			Point search(Mat s, Mat tpl, int x, int y, double* maxVal);
			void encodeIntra(Mat* frame);
			void encodeInter(Mat* aBlock, Mat* lBlock);
			bool decodeIntra(Mat* frame);
			bool decodeInter(Mat* aBlock, Mat* lBlock);
			uint predictMode;
			char mode;
			char thresholdMode;
			char searchMode;
			std::unique_ptr<VideoCoding::Golomb> golomb;
			string ifname;
			string ofname;
			uint blockSize;
			bool endDecode;
			bool endEncode;
			Mat lframe;
			Mat channels[3]; // 0 - blue ; 1 - green ; 2 - red
			int predValue[3]; // 0 - blue ; 1 - green ; 2 - red
			int decodedValue[3]; // 0 - blue ; 1 - green ; 2 - red
			double Kb, Kr;
			uint mB, mG, mR;
			uint rows, cols;
			uint fps;
			uint frameType, channelType;
			uint blocks = 0;
			uint totalBlocks = 0;
			uint searchArea;
			uint periodicity;
			uint framecount = 1;
			double t;
			double base_threshold;
			double ceil_threshold;
			double min_threshold;
			Mat dummy; // Dummy mat to show blocks not encoded.
	};
}
