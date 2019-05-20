#include "updatepatches.h"
#include "opencv2/tracking.hpp"
using namespace cv;
using namespace std;

int main()
{
    bool Status=true;

    Mat Img_1,PatchImage;

    vector<Rect2d> ObjRegion;
    Img_1=imread("E:\\2019Database\\countonme\\008.jpg");
    if((Img_1.rows>1000)||(Img_1.cols>1200))
    {
          resize(Img_1,Img_1,Size(Img_1.cols/2,Img_1.rows/2));
    }
    ////////////////////////////Use imread ////////////////////////////////////
    // PatchImage=imread("E:\\2019Database\\countonme\\035patch.jpg");
    ////////////////////////////////or/////////////////////////////////////////
    selectROI("crop your Object",Img_1,ObjRegion);
    imshow("selected region",Img_1(ObjRegion[0]));
    PatchImage=Img_1(ObjRegion[0]).clone();
    ///////////////////////////////////////////////////////////////////////////
    if(PatchImage.empty()||Img_1.empty())
    {
        cout<<"images not loaded correctly"<<endl;
        return -1;
    }

    //initiallise the structure parameters
    TemplatePatches Input;
    Input.Image=Img_1.clone();
    Input.Patches.push_back(PatchImage);
    Input.PatchNumber=0;
    Input.InitialPatch=PatchImage.clone();

    UpdatePatches Match;
    while(Status)
    {
        int PreviousPatchSize=Input.Patches.size();

        Status=Match.TemplateMatching(Input);

        cout<<"size of Rectangles"<<Input.candidatePatches.size()<<endl;
        if(Status)
        {
            for(int Index=0;Index<Input.candidatePatches.size();Index++)
            {
                //similarity check
                Input.Patches.push_back(Input.candidatePatches[Index]);

            }
            Input.candidatePatches.clear();
            Input.PatchNumber+=PreviousPatchSize;
            //Input.Image=Img_1.clone();

        }
        else
        {
            break;
        }
    }
    Match.RemoveOverlapedRois(Input.RoiOfPatches,.5);
    for(int loc=0;loc<Input.RoiOfPatches.size();loc++)
    {
        rectangle(Img_1,Input.RoiOfPatches[loc],Scalar(0,100,255),2);
    }

    imshow("resized input to see entire image",Img_1);
    imwrite("final.jpg",Img_1);
    cout<<"countRoi="<<Input.RoiOfPatches.size()<<endl;
    cout<<"countPatch="<<Input.Patches.size()<<endl;

    waitKey(0);
    return 0;
}

