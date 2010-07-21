/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Bunny.hpp"
#include <GL/glew.h>
#include <iostream>
#include <Maoni/Vector.hpp>
#include <boost/array.hpp>

#include <boost/la/all.hpp>
using namespace boost::la;

static float vertex_data[] = { 0.007426f, 0.057009f, 0.018721f, -0.007444f,
		0.052014f, 0.002792f, 0.009992f, 0.056341f, 0.003380f, -0.067141f,
		0.027025f, 0.007411f, -0.068082f, 0.027622f, 0.015982f, -0.066562f,
		0.014279f, 0.004118f, -0.062144f, 0.078115f, 0.004559f, -0.069873f,
		0.076123f, 0.012650f, -0.064047f, 0.070488f, 0.007702f, -0.052791f,
		0.106153f, -0.047962f, -0.056459f, 0.104026f, -0.050411f, -0.052786f,
		0.107274f, -0.054141f, -0.048112f, 0.108975f, -0.054646f, 0.005805f,
		-0.006866f, 0.053773f, -0.002651f, 0.007746f, 0.054792f, 0.003510f,
		0.010148f, 0.057988f, 0.031145f, 0.058200f, 0.000653f, 0.027854f,
		0.059693f, 0.013863f, 0.044716f, 0.051491f, 0.027614f, 0.052618f,
		0.044525f, 0.026281f, 0.041696f, 0.045661f, 0.034821f, -0.040177f,
		0.101744f, -0.055955f, -0.044642f, 0.099325f, -0.044137f, -0.064271f,
		0.066957f, 0.003062f, -0.060546f, 0.069710f, 0.001230f, -0.028049f,
		-0.019840f, 0.016639f, -0.030653f, -0.023856f, 0.025255f, -0.028366f,
		-0.025136f, 0.016077f, -0.057605f, 0.098846f, -0.042792f, -0.064356f,
		0.010465f, 0.006477f, -0.064966f, 0.013310f, 0.022969f, -0.064706f,
		0.007426f, 0.015020f, -0.041602f, 0.068961f, -0.006734f, -0.041620f,
		0.074637f, -0.020764f, -0.046548f, 0.067523f, -0.007818f, 0.001330f,
		0.085041f, -0.009136f, 0.004291f, 0.093008f, -0.019119f, -0.008724f,
		0.087161f, -0.013646f, -0.055490f, 0.061064f, 0.052524f, -0.050278f,
		0.041987f, 0.054066f, -0.059861f, 0.055672f, 0.053401f, -0.011163f,
		-0.022310f, -0.010957f, -0.013845f, -0.017918f, -0.010129f, -0.020133f,
		-0.025270f, -0.012003f, -0.053834f, 0.071447f, 0.046456f, -0.050505f,
		0.065140f, 0.048821f, -0.010922f, 0.079220f, -0.003826f, -0.021693f,
		0.078226f, -0.006150f, -0.014427f, 0.089707f, -0.014206f, -0.045411f,
		0.048918f, 0.052956f, -0.018195f, -0.037615f, 0.042475f, -0.016029f,
		-0.028053f, 0.040624f, -0.013329f, -0.036587f, 0.047193f, 0.012026f,
		0.048539f, 0.036839f, 0.017335f, 0.055759f, 0.028838f, 0.030873f,
		0.049977f, 0.035112f, -0.052588f, 0.035084f, 0.037391f, -0.045195f,
		0.037171f, 0.037562f, -0.051523f, 0.029616f, 0.037629f, -0.039048f,
		0.024051f, -0.018627f, -0.054782f, 0.024477f, -0.013155f, -0.048774f,
		0.009536f, -0.017884f, 0.032440f, 0.025600f, 0.049251f, 0.021330f,
		0.028893f, 0.044358f, 0.035238f, 0.029603f, 0.047379f, -0.046975f,
		0.073759f, -0.025852f, -0.051415f, 0.069749f, -0.007451f, 0.079140f,
		-0.023105f, 0.007237f, 0.076383f, -0.012714f, -0.002235f, 0.070898f,
		-0.021979f, -0.005356f, -0.041276f, 0.087084f, -0.047353f, -0.048290f,
		0.075332f, -0.037411f, 0.033871f, 0.041322f, 0.038286f, -0.068846f,
		0.018312f, 0.016215f, 0.022329f, -0.015086f, 0.054589f, 0.023184f,
		-0.010663f, 0.057393f, 0.030952f, -0.014207f, 0.053019f, 0.023329f,
		-0.028577f, 0.045973f, 0.029948f, -0.025352f, 0.050622f, 0.035069f,
		-0.027253f, 0.044499f, 0.020859f, -0.020140f, 0.054827f, 0.026511f,
		-0.003708f, 0.055548f, 0.030856f, -0.005351f, 0.054898f, -0.026463f,
		0.063965f, 0.015501f, -0.028112f, 0.070202f, 0.008751f, -0.027127f,
		0.062031f, 0.002195f, -0.039627f, 0.029187f, 0.042772f, 0.026838f,
		0.007243f, 0.055901f, 0.035663f, 0.011041f, 0.052870f, 0.029610f,
		0.001705f, 0.056906f, 0.061851f, -0.033232f, 0.002266f, -0.004072f,
		0.053407f, 0.012362f, -0.008528f, 0.046313f, 0.029499f, -0.016264f,
		0.049742f, 0.027942f, -0.042600f, 0.016738f, 0.045868f, -0.049566f,
		0.021313f, 0.042176f, -0.024099f, 0.094735f, 0.002769f, -0.014373f,
		0.103362f, -0.005226f, -0.009851f, 0.102345f, -0.002701f, 0.020152f,
		0.001668f, 0.059404f, 0.020622f, 0.008077f, 0.057798f, 0.040295f,
		0.018928f, 0.047817f, -0.039687f, 0.080201f, 0.000731f, -0.049853f,
		0.084876f, -0.002108f, -0.043989f, 0.088111f, -0.012385f, -0.037142f,
		0.002204f, 0.042404f, -0.031914f, 0.016947f, 0.044992f, -0.028163f,
		0.019370f, 0.044265f, 0.021183f, -0.002500f, 0.057227f, 0.045285f,
		0.023826f, 0.046687f, 0.038929f, 0.006807f, 0.053521f, 0.066514f,
		0.026465f, 0.004061f, 0.054528f, 0.029846f, -0.014251f, 0.063550f,
		0.018786f, -0.008105f, 0.008987f, 0.019337f, 0.056713f, 0.020508f,
		0.021189f, 0.055885f, 0.025685f, 0.012054f, 0.057697f, -0.025564f,
		0.036134f, 0.039143f, -0.032688f, -0.027685f, 0.045231f, -0.038497f,
		-0.025618f, 0.040629f, -0.029680f, -0.023725f, 0.037644f, -0.033449f,
		0.009209f, 0.045283f, -0.010584f, -0.013230f, -0.012900f, 0.053513f,
		0.044371f, -0.000229f, 0.012991f, 0.093705f, -0.020840f, 0.013595f,
		0.105141f, -0.031210f, -0.033250f, 0.041943f, 0.035044f, -0.003793f,
		-0.037527f, 0.053914f, -0.009822f, -0.037408f, 0.050830f, -0.009870f,
		-0.032600f, 0.052852f, -0.019168f, 0.022400f, 0.042218f, 0.012579f,
		0.025202f, 0.052194f, 0.022025f, 0.025601f, 0.051879f, -0.025266f,
		0.000247f, 0.041563f, -0.025243f, 0.014145f, 0.045404f, 0.082927f,
		-0.012093f, 0.008939f, -0.025403f, 0.046591f, 0.030108f, -0.034253f,
		0.082807f, 0.013016f, -0.024562f, 0.085930f, 0.008150f, -0.028833f,
		0.077158f, 0.013075f, 0.032212f, 0.056079f, 0.027713f, -0.023423f,
		0.074003f, -0.002654f, -0.025856f, -0.030041f, 0.044054f, -0.030876f,
		-0.033938f, 0.047094f, 0.014825f, 0.033833f, 0.044167f, 0.026368f,
		0.040971f, 0.041561f, 0.053929f, -0.023708f, 0.032983f, 0.062394f,
		-0.024913f, 0.032376f, 0.058849f, -0.032898f, 0.025170f, -0.020175f,
		0.013246f, 0.042446f, -0.019834f, -0.019872f, 0.039788f, -0.015255f,
		0.008057f, 0.043590f, -0.016314f, 0.036991f, 0.036665f, -0.014893f,
		-0.005681f, 0.042100f, -0.028136f, 0.069785f, 0.004040f, 0.037507f,
		0.019403f, 0.051122f, -0.006786f, -0.019966f, 0.036426f, -0.009308f,
		0.024997f, 0.044867f, -0.037413f, 0.075559f, 0.036041f, -0.069189f,
		0.062379f, 0.018211f, -0.033614f, 0.080685f, 0.029230f, -0.008733f,
		0.004654f, 0.041096f, 0.004315f, 0.037211f, 0.041098f, -0.008641f,
		0.014757f, 0.043818f, -0.061502f, 0.004949f, 0.021010f, -0.061718f,
		0.002904f, 0.003966f, -0.005057f, -0.006611f, 0.039165f, -0.000553f,
		0.023098f, 0.045836f, 0.042620f, 0.054485f, 0.010313f, 0.064368f,
		-0.008364f, 0.029187f, -0.002329f, -0.024402f, 0.050261f, 0.002019f,
		-0.022342f, 0.045937f, -0.033354f, 0.079607f, -0.002604f, -0.001136f,
		-0.028467f, 0.054001f, -0.034042f, -0.018650f, 0.007796f, -0.036546f,
		-0.014655f, 0.003012f, -0.033720f, -0.015531f, 0.009470f, -0.030971f,
		-0.014890f, 0.022251f, -0.066737f, 0.075446f, 0.032167f, -0.052017f,
		0.084855f, 0.023383f, -0.055454f, 0.079237f, 0.035881f, 0.066844f,
		0.005827f, -0.000945f, -0.070111f, 0.076628f, 0.022562f, 0.002430f,
		0.021860f, 0.053240f, 0.005821f, 0.027127f, 0.043960f, -0.002011f,
		0.015126f, 0.054061f, -0.038781f, 0.100056f, -0.062318f, -0.040342f,
		0.090522f, -0.058971f, 0.070026f, 0.000712f, 0.014815f, 0.068980f,
		-0.001009f, 0.005054f, 0.008554f, 0.089636f, -0.014817f, 0.006161f,
		0.087581f, -0.009944f, 0.002855f, 0.087571f, -0.005047f, 0.005190f,
		-0.018807f, 0.050492f, 0.011523f, -0.023307f, 0.050378f, 0.071459f,
		-0.029757f, 0.010192f, 0.011827f, -0.017371f, 0.052623f, 0.069664f,
		-0.009932f, 0.031262f, 0.011928f, -0.011327f, 0.056074f, -0.035918f,
		0.065667f, -0.005556f, 0.075313f, -0.017273f, 0.028481f, 0.078165f,
		-0.007776f, 0.026913f, 0.079456f, -0.020170f, 0.021390f, 0.037646f,
		-0.017126f, 0.048973f, -0.013198f, 0.004840f, -0.019785f, -0.013070f,
		0.009256f, -0.024210f, -0.018961f, 0.011333f, -0.021248f, -0.039764f,
		0.073840f, -0.004333f, 0.056729f, -0.011590f, 0.039244f, 0.048045f,
		0.008804f, 0.048345f, -0.030812f, 0.071533f, -0.000927f, -0.039089f,
		0.052083f, 0.042641f, -0.040697f, 0.065359f, 0.035913f, 0.049400f,
		0.032040f, 0.038279f, 0.056866f, 0.019043f, 0.040097f, 0.036411f,
		-0.037669f, 0.044202f, -0.035447f, -0.037858f, 0.046398f, -0.036450f,
		-0.034150f, 0.046873f, 0.042263f, -0.016277f, 0.048874f, 0.003429f,
		0.105414f, -0.018088f, 0.000317f, 0.112950f, -0.013308f, -0.027550f,
		-0.037685f, 0.045847f, -0.026565f, 0.057667f, 0.030121f, -0.031668f,
		0.065141f, 0.029164f, 0.083246f, -0.003610f, 0.017888f, 0.041911f,
		-0.008945f, 0.048333f, -0.031619f, 0.073468f, 0.023408f, -0.041228f,
		-0.032912f, 0.042948f, -0.007192f, 0.097034f, -0.009370f, 0.003860f,
		0.096529f, -0.014825f, 0.057341f, 0.005396f, 0.039079f, 0.051577f,
		0.040477f, 0.032399f, 0.063751f, 0.027985f, 0.025030f, 0.004825f,
		0.115476f, -0.021528f, 0.008818f, 0.090831f, -0.012152f, -0.020583f,
		0.075457f, 0.004408f, -0.013373f, 0.080893f, 0.001571f, -0.016506f,
		0.088678f, 0.000121f, 0.072158f, -0.027787f, 0.021763f, -0.043975f,
		0.108297f, -0.060411f, -0.022505f, 0.081542f, 0.007676f, -0.035145f,
		-0.017880f, 0.001102f, -0.037167f, -0.024479f, 0.002363f, -0.013350f,
		0.085990f, 0.003378f, -0.056299f, 0.080094f, 0.000108f, -0.062583f,
		0.080806f, 0.010967f, 0.015722f, -0.036931f, 0.048560f, -0.066256f,
		0.068817f, 0.039494f, -0.068330f, 0.056934f, 0.041881f, -0.065414f,
		0.019652f, 0.026393f, -0.062896f, 0.014380f, 0.028377f, -0.043830f,
		-0.037462f, 0.040392f, -0.070188f, 0.059069f, 0.026150f, -0.073258f,
		0.052173f, 0.020919f, -0.067024f, 0.064408f, 0.025583f, -0.069770f,
		0.042998f, 0.007885f, -0.072493f, 0.046965f, 0.024047f, -0.070439f,
		0.040864f, 0.016239f, -0.040285f, -0.038217f, 0.021965f, -0.042450f,
		-0.028143f, 0.033925f, -0.061618f, 0.007682f, 0.028786f, -0.040088f,
		0.088390f, -0.025115f, -0.039987f, 0.090686f, -0.038494f, 0.043832f,
		-0.027775f, -0.018486f, 0.053204f, -0.024325f, -0.007293f, 0.049980f,
		-0.021221f, -0.019852f, -0.007387f, 0.098251f, -0.018121f, -0.068249f,
		0.060941f, 0.004800f, -0.024743f, 0.056795f, 0.002101f, -0.016897f,
		0.051445f, -0.009491f, 0.054286f, 0.018338f, -0.018435f, 0.061257f,
		0.012427f, -0.015146f, -0.044040f, -0.039545f, -0.008106f, -0.032510f,
		-0.033226f, -0.010737f, -0.045115f, -0.033749f, -0.006480f, 0.042214f,
		-0.037942f, -0.001498f, 0.035388f, -0.038228f, -0.020823f, 0.061272f,
		-0.014177f, -0.004866f, -0.006613f, 0.021191f, -0.024980f, -0.014842f,
		0.031468f, -0.021176f, -0.015985f, 0.017279f, -0.023774f, 0.079253f,
		-0.003794f, 0.002948f, 0.022331f, -0.036612f, -0.025127f, 0.011243f,
		-0.039011f, -0.023551f, 0.051320f, 0.003721f, -0.022322f, 0.046973f,
		-0.036905f, 0.026673f, -0.065205f, 0.036650f, 0.015204f, -0.065400f,
		0.051734f, -0.002437f, -0.021016f, -0.001778f, -0.017803f, -0.046381f,
		0.080999f, -0.052012f, -0.050332f, 0.077443f, -0.041640f, -0.061338f,
		0.038016f, 0.000936f, -0.071130f, 0.041720f, 0.034852f, -0.070809f,
		0.049396f, 0.029036f, -0.070831f, 0.048574f, 0.044145f, -0.027990f,
		0.019950f, -0.021542f, 0.057316f, 0.042881f, 0.011682f, -0.052740f,
		0.076298f, -0.028201f, -0.038776f, 0.083080f, 0.008275f, -0.050178f,
		0.083460f, 0.003375f, 0.076725f, 0.000826f, 0.010044f, 0.075451f,
		0.000840f, 0.020493f, -0.023283f, -0.033453f, -0.021692f, -0.020872f,
		-0.038770f, -0.027531f, -0.012648f, -0.029955f, -0.030505f, -0.054538f,
		0.083241f, -0.006242f, -0.020702f, 0.054699f, 0.017395f, -0.021795f,
		0.057154f, 0.011154f, -0.041066f, 0.080317f, 0.034293f, -0.053907f,
		0.100237f, -0.035656f, -0.058445f, -0.002051f, 0.015377f, -0.049901f,
		0.098485f, -0.029343f, -0.055454f, 0.089440f, -0.016232f, -0.030471f,
		-0.022334f, 0.031658f, 0.043666f, 0.046134f, -0.010444f, -0.018708f,
		0.100651f, -0.008291f, -0.029464f, -0.010581f, 0.031862f, -0.025514f,
		-0.020108f, 0.037026f, -0.027900f, 0.093670f, -0.003788f, -0.059756f,
		0.023281f, 0.033259f, -0.057212f, 0.012994f, 0.037058f, -0.063302f,
		0.043150f, 0.049440f, -0.063066f, 0.049918f, 0.049108f, -0.058697f,
		0.044072f, 0.048607f, -0.046963f, 0.007720f, 0.041296f, -0.052947f,
		-0.001523f, 0.032145f, 0.027868f, -0.037883f, -0.015137f, -0.055760f,
		0.034691f, 0.034436f, -0.045603f, -0.038001f, 0.031337f, -0.017592f,
		-0.010522f, -0.012601f, -0.021681f, -0.018236f, -0.011227f, -0.052174f,
		0.041810f, -0.006667f, -0.063487f, 0.022922f, -0.004149f, -0.065873f,
		0.039034f, 0.041471f, -0.047530f, -0.028093f, 0.006745f, -0.039962f,
		-0.030990f, 0.015441f, -0.051155f, -0.036697f, 0.007543f, -0.005675f,
		-0.012036f, -0.029556f, 0.000219f, -0.000141f, -0.039127f, -0.009564f,
		0.003268f, -0.032996f, -0.061762f, 0.037141f, 0.025645f, -0.059391f,
		0.060020f, -0.003721f, -0.051693f, 0.056261f, -0.009146f, -0.034558f,
		-0.025551f, 0.011025f, -0.034523f, 0.087236f, 0.001469f, -0.006393f,
		0.009517f, -0.036564f, -0.016486f, 0.097274f, -0.012217f, -0.041992f,
		0.098620f, -0.061360f, -0.044107f, 0.089464f, -0.058645f, 0.014768f,
		0.038261f, -0.022165f, 0.021296f, 0.038506f, -0.019917f, 0.018471f,
		0.044170f, -0.015922f, -0.050039f, 0.100685f, -0.051353f, -0.048339f,
		0.089636f, -0.047953f, -0.013455f, 0.046112f, -0.011731f, -0.001763f,
		0.044792f, -0.014166f, -0.007807f, 0.049848f, -0.004577f, -0.052197f,
		0.092464f, -0.039484f, -0.018592f, -0.027128f, -0.021682f, 0.016298f,
		0.053748f, -0.007975f, 0.006055f, 0.052381f, -0.004338f, -0.053013f,
		0.081288f, -0.018900f, 0.034674f, 0.016975f, -0.030702f, 0.038286f,
		0.024174f, -0.023600f, -0.005341f, 0.018178f, -0.034373f, -0.006973f,
		-0.022611f, -0.022627f, -0.000808f, -0.025619f, -0.027504f, -0.055940f,
		0.083306f, -0.017706f, -0.068525f, 0.043254f, 0.028310f, -0.054446f,
		0.076440f, -0.014414f, -0.027661f, -0.038789f, -0.013257f, -0.053955f,
		0.078639f, -0.008892f, -0.006999f, 0.105436f, -0.015797f, 0.010479f,
		-0.035021f, -0.026474f, -0.007270f, -0.039179f, -0.029602f, 0.005300f,
		-0.038925f, -0.020161f, 0.038115f, 0.028839f, -0.023095f, -0.059541f,
		0.009449f, -0.006040f, -0.056409f, 0.074485f, -0.003370f, -0.030794f,
		-0.025342f, -0.008166f, -0.014778f, 0.039842f, -0.018048f, 0.010980f,
		0.027225f, -0.024441f, 0.028953f, 0.027224f, -0.021842f, -0.043649f,
		-0.029569f, -0.002830f, -0.038398f, -0.029841f, -0.006671f, -0.030539f,
		-0.020364f, -0.007483f, -0.051044f, -0.037206f, 0.001036f, -0.053126f,
		-0.001051f, -0.006575f, -0.012793f, -0.037936f, 0.045055f, 0.034303f,
		0.039027f, -0.018503f, 0.029480f, 0.052197f, -0.010122f, 0.037158f,
		0.032807f, -0.018733f, 0.021661f, 0.022086f, -0.032522f, 0.072224f,
		-0.009756f, -0.003362f, -0.036528f, 0.074589f, -0.001443f, 0.006540f,
		0.035223f, -0.020823f, 0.009469f, 0.022787f, -0.034186f, -0.041453f,
		0.046633f, -0.009955f, -0.037147f, 0.039112f, -0.016811f, -0.029752f,
		0.048068f, -0.012726f, -0.028373f, 0.055731f, -0.003712f, -0.026044f,
		0.029757f, -0.021455f, 0.019698f, 0.010792f, -0.037605f, -0.000314f,
		0.104228f, -0.022474f, -0.033176f, 0.017706f, -0.022578f, -0.033805f,
		0.008921f, -0.021740f, 0.064017f, -0.020082f, -0.007309f, -0.032694f,
		-0.008184f, -0.008972f, -0.034747f, 0.029840f, -0.018978f, -0.041072f,
		0.030952f, -0.018056f, -0.042888f, -0.010714f, -0.002783f, -0.041657f,
		-0.001626f, -0.015811f, 0.019991f, -0.035010f, 0.004970f, 0.021056f,
		-0.037796f, 0.011439f, 0.023772f, -0.038152f, 0.003633f, -0.032208f,
		0.027082f, -0.021838f, -0.026853f, -0.009273f, -0.012386f, -0.027464f,
		-0.002955f, -0.014539f, 0.042072f, -0.018392f, -0.027537f, 0.031073f,
		-0.001676f, -0.032666f, 0.004237f, 0.014182f, -0.038660f, 0.038391f,
		-0.024260f, -0.024152f, 0.028721f, -0.024033f, -0.029432f, 0.025226f,
		-0.030861f, -0.024137f, 0.011366f, -0.026783f, -0.029824f, 0.008117f,
		-0.009916f, -0.036864f, 0.004205f, -0.027719f, -0.027790f, -0.007479f,
		-0.034118f, -0.017556f, 0.028703f, -0.033415f, -0.010681f, 0.035037f,
		-0.037927f, 0.030056f, 0.042938f, -0.038395f, 0.004670f, 0.055046f,
		-0.037475f, 0.011210f, 0.022635f, -0.038872f, 0.014019f, 0.032617f,
		-0.038246f, -0.010636f, -0.060351f, 0.038043f, 0.043649f, -0.048802f,
		-0.011165f, 0.015950f, -0.041718f, -0.039379f, 0.001285f, -0.041662f,
		-0.006892f, 0.033093f, -0.032203f, -0.038961f, 0.021632f, -0.020905f,
		-0.039430f, -0.013866f, -0.011179f, -0.038847f, -0.020380f, };

static unsigned short index_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9,
		11, 12, 13, 14, 15, 0, 16, 17, 18, 19, 20, 21, 22, 12, 23, 24, 8, 25,
		26, 27, 9, 28, 10, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
		42, 43, 44, 45, 38, 46, 35, 47, 47, 37, 48, 38, 49, 39, 50, 51, 52, 53,
		54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 34, 65, 66, 67, 68, 69, 33,
		70, 71, 63, 72, 64, 5, 73, 29, 74, 75, 76, 77, 78, 79, 77, 80, 78, 81,
		82, 75, 80, 76, 78, 83, 84, 85, 86, 58, 57, 80, 74, 76, 87, 88, 89, 90,
		67, 69, 91, 92, 93, 94, 95, 86, 96, 97, 98, 92, 91, 0, 99, 15, 100, 62,
		64, 101, 99, 100, 87, 102, 103, 104, 105, 94, 106, 94, 86, 107, 108,
		81, 75, 101, 109, 110, 111, 112, 113, 54, 0, 17, 114, 115, 116, 107,
		106, 94, 86, 57, 117, 108, 99, 87, 118, 119, 120, 106, 121, 105, 41,
		122, 42, 123, 112, 111, 124, 125, 36, 126, 117, 57, 127, 128, 129, 117,
		130, 107, 117, 107, 86, 115, 131, 132, 121, 133, 105, 121, 106, 134,
		81, 89, 82, 87, 89, 81, 67, 135, 68, 106, 107, 134, 121, 134, 133, 136,
		117, 126, 137, 138, 139, 140, 54, 17, 141, 46, 47, 118, 142, 143, 120,
		142, 118, 117, 136, 93, 100, 116, 87, 144, 53, 145, 146, 147, 148, 120,
		51, 142, 133, 134, 149, 107, 149, 134, 33, 65, 34, 120, 150, 51, 133,
		149, 151, 117, 152, 130, 93, 152, 117, 96, 98, 138, 133, 153, 150, 107,
		130, 149, 84, 154, 85, 144, 145, 63, 55, 54, 140, 24, 6, 8, 53, 55,
		145, 149, 130, 151, 132, 62, 115, 62, 155, 115, 150, 153, 156, 133,
		151, 153, 130, 152, 157, 45, 44, 158, 159, 23, 8, 156, 51, 150, 93, 92,
		152, 139, 160, 137, 130, 161, 151, 151, 161, 153, 157, 152, 162, 130,
		163, 161, 16, 0, 2, 153, 161, 156, 163, 130, 157, 152, 92, 162, 92, 0,
		54, 164, 165, 31, 161, 166, 156, 157, 167, 163, 168, 17, 16, 169, 147,
		146, 170, 156, 171, 141, 47, 172, 72, 63, 145, 129, 170, 173, 167, 157,
		162, 174, 175, 176, 55, 20, 72, 108, 87, 81, 25, 177, 26, 178, 179,
		180, 110, 88, 101, 170, 171, 173, 181, 111, 113, 178, 182, 179, 171,
		77, 173, 183, 184, 131, 162, 92, 53, 15, 185, 114, 185, 183, 114, 70,
		186, 187, 188, 181, 189, 35, 190, 36, 191, 35, 192, 193, 194, 171, 195,
		67, 90, 193, 196, 194, 13, 196, 193, 184, 162, 144, 64, 109, 101, 169,
		197, 147, 171, 194, 77, 162, 53, 144, 15, 114, 100, 183, 131, 114, 114,
		116, 100, 115, 155, 116, 114, 131, 115, 196, 74, 80, 198, 74, 196, 15,
		99, 13, 196, 80, 194, 165, 29, 31, 198, 75, 74, 13, 75, 198, 194, 80,
		77, 13, 108, 75, 99, 108, 13, 85, 154, 199, 200, 201, 202, 78, 76, 203,
		204, 205, 206, 32, 207, 33, 87, 116, 88, 146, 208, 169, 82, 110, 209,
		141, 172, 210, 39, 49, 57, 45, 211, 49, 158, 212, 45, 213, 214, 109,
		45, 212, 211, 57, 49, 211, 146, 215, 79, 216, 217, 143, 218, 208, 79,
		109, 64, 213, 203, 218, 79, 211, 126, 57, 219, 98, 220, 143, 217, 118,
		143, 142, 221, 211, 212, 222, 158, 223, 212, 221, 142, 50, 224, 135,
		202, 225, 218, 203, 126, 211, 136, 211, 222, 136, 212, 223, 222, 158,
		160, 226, 118, 217, 227, 228, 98, 219, 229, 219, 124, 228, 219, 229,
		110, 109, 209, 230, 109, 214, 142, 51, 50, 231, 232, 214, 110, 89, 88,
		233, 124, 219, 234, 228, 229, 208, 146, 79, 45, 49, 38, 235, 236, 46,
		213, 20, 231, 88, 155, 101, 222, 223, 83, 208, 225, 230, 155, 88, 116,
		158, 226, 223, 218, 225, 208, 46, 236, 192, 237, 228, 234, 203, 79, 78,
		234, 124, 190, 197, 200, 147, 147, 200, 238, 188, 111, 181, 75, 82, 76,
		238, 200, 202, 82, 209, 225, 239, 186, 21, 208, 230, 169, 82, 225, 76,
		138, 240, 139, 169, 230, 214, 241, 174, 242, 84, 139, 235, 139, 240,
		235, 243, 192, 236, 76, 225, 203, 219, 220, 233, 234, 191, 192, 231,
		214, 213, 235, 240, 236, 240, 138, 237, 197, 201, 200, 225, 209, 230,
		6, 244, 245, 62, 101, 155, 231, 20, 19, 209, 109, 230, 240, 237, 243,
		236, 240, 243, 64, 72, 213, 213, 72, 20, 173, 77, 246, 89, 110, 82,
		237, 138, 98, 55, 72, 145, 237, 98, 228, 169, 214, 188, 63, 184, 144,
		243, 237, 192, 234, 229, 124, 192, 237, 234, 73, 30, 29, 247, 40, 248,
		30, 249, 250, 251, 227, 217, 159, 252, 253, 159, 254, 252, 159, 182,
		254, 255, 256, 257, 258, 26, 259, 255, 253, 256, 191, 190, 35, 250,
		260, 164, 261, 22, 262, 263, 264, 265, 37, 266, 48, 267, 23, 159, 1,
		268, 269, 270, 271, 113, 272, 273, 274, 275, 263, 276, 264, 277, 265,
		267, 159, 253, 33, 262, 70, 154, 84, 235, 278, 279, 280, 224, 281, 135,
		276, 282, 283, 181, 271, 284, 215, 146, 285, 207, 104, 261, 7, 159, 8,
		3, 286, 4, 181, 284, 277, 287, 267, 255, 204, 288, 122, 7, 182, 159,
		275, 264, 263, 289, 290, 71, 255, 286, 291, 189, 181, 277, 181, 113,
		271, 292, 293, 294, 291, 286, 3, 207, 261, 262, 5, 4, 73, 33, 207, 262,
		214, 232, 188, 277, 284, 265, 164, 30, 250, 255, 257, 286, 205, 280,
		206, 280, 295, 206, 70, 21, 186, 70, 187, 289, 223, 226, 84, 160, 139,
		226, 223, 84, 83, 224, 202, 201, 135, 67, 202, 232, 296, 111, 262, 21,
		70, 188, 232, 111, 21, 262, 22, 226, 139, 84, 67, 195, 202, 102, 104,
		207, 65, 297, 66, 21, 12, 239, 298, 299, 102, 233, 125, 124, 224, 300,
		281, 224, 301, 300, 302, 303, 304, 169, 188, 301, 299, 305, 103, 301,
		188, 300, 37, 36, 266, 254, 178, 248, 179, 182, 245, 299, 103, 102,
		300, 188, 189, 138, 137, 96, 70, 289, 71, 91, 93, 306, 1, 307, 268,
		154, 141, 210, 232, 231, 19, 160, 308, 179, 244, 299, 245, 299, 179,
		245, 309, 9, 22, 261, 104, 22, 35, 37, 47, 298, 179, 299, 165, 164,
		310, 311, 312, 309, 85, 307, 83, 299, 244, 305, 306, 307, 91, 252, 293,
		253, 91, 307, 1, 103, 312, 311, 12, 22, 9, 6, 245, 7, 98, 97, 220, 136,
		306, 93, 19, 296, 232, 296, 123, 111, 306, 136, 222, 0, 91, 1, 158, 44,
		308, 259, 313, 119, 44, 180, 308, 311, 309, 22, 308, 180, 179, 103,
		311, 104, 160, 179, 137, 137, 179, 298, 241, 175, 174, 18, 296, 19,
		190, 124, 36, 222, 83, 306, 296, 168, 123, 259, 26, 313, 160, 158, 308,
		18, 168, 296, 132, 63, 62, 22, 104, 311, 168, 16, 123, 123, 16, 314,
		63, 132, 184, 132, 131, 184, 18, 17, 168, 97, 315, 220, 18, 140, 17,
		309, 28, 9, 83, 307, 306, 18, 20, 140, 316, 133, 317, 161, 13, 166,
		154, 235, 141, 51, 170, 129, 95, 58, 86, 120, 313, 317, 163, 167, 185,
		156, 166, 171, 97, 96, 318, 317, 133, 150, 191, 234, 190, 96, 137, 298,
		33, 71, 65, 52, 51, 129, 196, 13, 198, 35, 46, 192, 167, 183, 185, 278,
		280, 205, 316, 317, 313, 185, 15, 14, 103, 305, 312, 319, 95, 320, 321,
		322, 323, 227, 119, 118, 129, 173, 127, 320, 324, 325, 166, 13, 171,
		14, 163, 185, 40, 322, 294, 283, 326, 276, 247, 44, 40, 197, 301, 201,
		44, 38, 40, 327, 56, 58, 328, 259, 251, 184, 183, 167, 42, 329, 330,
		58, 95, 319, 323, 322, 40, 288, 329, 122, 167, 162, 184, 331, 332, 60,
		141, 235, 46, 320, 95, 94, 320, 94, 324, 317, 150, 120, 94, 105, 324,
		333, 294, 321, 323, 40, 39, 13, 193, 171, 334, 335, 336, 122, 329, 42,
		180, 44, 247, 119, 313, 120, 321, 294, 322, 182, 178, 254, 337, 338,
		339, 260, 325, 164, 249, 319, 250, 327, 58, 319, 335, 334, 242, 51,
		156, 170, 249, 340, 319, 279, 295, 280, 335, 258, 336, 14, 13, 161, 34,
		341, 342, 250, 320, 260, 327, 319, 340, 174, 25, 27, 319, 320, 250,
		251, 259, 119, 7, 245, 182, 163, 14, 161, 242, 343, 335, 251, 119, 227,
		298, 344, 96, 338, 345, 339, 266, 346, 48, 294, 248, 40, 178, 180, 247,
		343, 27, 335, 204, 206, 288, 343, 174, 27, 187, 347, 348, 349, 350,
		351, 239, 11, 352, 347, 352, 353, 289, 348, 353, 347, 353, 348, 11, 10,
		352, 354, 355, 356, 352, 357, 353, 10, 28, 352, 352, 28, 357, 289, 353,
		290, 97, 318, 315, 43, 358, 41, 174, 343, 242, 290, 297, 71, 351, 359,
		360, 357, 361, 353, 290, 353, 361, 362, 270, 363, 328, 258, 259, 205,
		345, 364, 365, 304, 366, 290, 361, 297, 25, 174, 176, 339, 345, 205,
		12, 11, 239, 339, 205, 204, 205, 364, 278, 177, 316, 313, 4, 340, 73,
		339, 204, 337, 28, 367, 357, 249, 30, 73, 204, 122, 337, 357, 367, 361,
		178, 247, 248, 368, 256, 293, 297, 361, 369, 252, 248, 293, 369, 66,
		297, 358, 43, 302, 337, 122, 365, 273, 272, 370, 305, 371, 312, 254,
		248, 252, 361, 371, 369, 258, 27, 26, 361, 367, 371, 372, 233, 220,
		303, 302, 370, 312, 367, 28, 43, 370, 302, 293, 256, 253, 283, 373,
		374, 374, 375, 283, 363, 270, 376, 60, 377, 61, 369, 378, 66, 177, 313,
		26, 31, 30, 164, 372, 315, 346, 370, 379, 273, 371, 378, 369, 335, 27,
		258, 286, 340, 4, 347, 239, 352, 248, 294, 293, 360, 359, 2, 380, 279,
		355, 312, 28, 309, 376, 270, 112, 60, 332, 377, 371, 305, 378, 255,
		267, 253, 279, 278, 381, 364, 381, 278, 293, 292, 368, 66, 378, 341,
		305, 244, 378, 382, 363, 376, 383, 384, 242, 384, 379, 242, 379, 385,
		242, 41, 304, 365, 332, 5, 377, 332, 331, 291, 385, 175, 241, 341, 378,
		24, 344, 172, 318, 377, 5, 29, 386, 383, 334, 377, 165, 387, 23, 267,
		287, 378, 244, 24, 318, 96, 344, 242, 385, 241, 287, 255, 291, 340,
		249, 73, 332, 3, 5, 332, 291, 3, 24, 244, 6, 29, 165, 377, 128, 127,
		388, 284, 271, 270, 389, 314, 390, 283, 375, 326, 383, 242, 334, 376,
		391, 382, 392, 362, 363, 351, 350, 390, 1, 269, 356, 314, 391, 112,
		270, 113, 112, 303, 374, 304, 189, 277, 393, 123, 314, 112, 68, 135,
		281, 314, 16, 390, 359, 390, 16, 355, 360, 356, 391, 376, 112, 392,
		363, 382, 347, 187, 186, 393, 68, 281, 315, 372, 220, 207, 394, 102,
		356, 360, 1, 32, 199, 394, 344, 102, 172, 189, 281, 300, 355, 279, 395,
		396, 392, 381, 207, 32, 394, 397, 398, 399, 304, 358, 302, 355, 395,
		351, 358, 304, 41, 172, 346, 318, 199, 400, 85, 397, 399, 400, 399,
		398, 380, 224, 201, 301, 398, 401, 380, 355, 351, 360, 2, 359, 16, 400,
		268, 85, 360, 2, 1, 399, 269, 400, 395, 349, 351, 400, 269, 268, 392,
		396, 402, 189, 393, 281, 351, 390, 359, 233, 372, 403, 381, 392, 382,
		380, 355, 354, 269, 399, 354, 315, 318, 346, 268, 307, 85, 364, 396,
		381, 380, 354, 399, 350, 389, 390, 269, 354, 356, 274, 273, 384, 68,
		393, 69, 287, 341, 23, 404, 59, 405, 69, 393, 406, 385, 407, 175, 59,
		408, 409, 393, 277, 406, 410, 411, 387, 397, 342, 331, 66, 341, 34,
		233, 403, 125, 277, 264, 406, 406, 264, 69, 331, 342, 287, 282, 373,
		283, 405, 59, 61, 342, 341, 287, 397, 331, 60, 412, 413, 414, 411, 405,
		61, 401, 398, 408, 415, 408, 59, 264, 275, 69, 210, 199, 154, 397, 60,
		409, 199, 210, 394, 388, 52, 128, 401, 415, 295, 47, 48, 172, 61, 377,
		387, 341, 24, 23, 330, 416, 385, 411, 61, 387, 291, 331, 287, 329, 288,
		416, 385, 416, 407, 407, 417, 411, 265, 284, 418, 288, 206, 417, 265,
		418, 263, 186, 239, 347, 350, 349, 382, 397, 199, 32, 284, 419, 418,
		172, 102, 394, 411, 417, 405, 270, 362, 284, 175, 407, 410, 346, 172,
		48, 407, 411, 410, 284, 362, 419, 383, 386, 274, 345, 420, 364, 418,
		421, 263, 371, 367, 312, 263, 421, 276, 295, 405, 206, 404, 415, 59,
		295, 279, 401, 391, 314, 389, 273, 379, 384, 43, 379, 370, 418, 422,
		421, 380, 401, 279, 396, 420, 402, 421, 423, 276, 421, 422, 423, 419,
		422, 418, 423, 282, 276, 391, 389, 382, 398, 397, 409, 419, 362, 402,
		43, 330, 385, 329, 416, 330, 392, 402, 362, 382, 389, 350, 385, 379,
		43, 32, 342, 397, 422, 424, 423, 282, 423, 373, 422, 419, 425, 416,
		288, 417, 382, 349, 381, 423, 426, 373, 400, 199, 397, 342, 32, 34,
		424, 426, 423, 210, 172, 394, 349, 395, 381, 425, 424, 422, 365, 122,
		41, 416, 417, 407, 206, 405, 417, 102, 344, 298, 402, 425, 419, 368,
		257, 256, 384, 383, 274, 425, 366, 424, 36, 125, 403, 402, 338, 425,
		381, 395, 279, 295, 415, 404, 426, 424, 366, 366, 425, 338, 396, 364,
		420, 366, 338, 337, 402, 420, 338, 274, 386, 272, 427, 428, 375, 401,
		408, 415, 426, 374, 373, 408, 398, 409, 36, 403, 266, 338, 420, 345,
		295, 404, 405, 60, 59, 409, 403, 372, 266, 366, 337, 365, 42, 330, 43,
		266, 372, 346, 53, 92, 54, 304, 374, 426, 426, 366, 304, 285, 429, 215,
		148, 238, 195, 430, 429, 285, 301, 197, 169, 275, 430, 431, 71, 297,
		65, 195, 238, 202, 257, 340, 286, 257, 368, 340, 148, 147, 238, 77,
		215, 246, 90, 431, 195, 413, 432, 414, 430, 285, 431, 428, 427, 412,
		428, 433, 326, 368, 327, 340, 292, 327, 368, 431, 148, 195, 292, 333,
		327, 275, 431, 90, 275, 90, 69, 375, 428, 326, 333, 321, 434, 310, 435,
		165, 164, 325, 310, 333, 292, 294, 56, 327, 333, 433, 432, 430, 216,
		143, 221, 289, 187, 348, 333, 434, 56, 321, 323, 434, 435, 410, 387,
		165, 435, 387, 310, 325, 435, 429, 246, 215, 246, 127, 173, 434, 39,
		56, 323, 39, 434, 140, 20, 55, 57, 56, 39, 435, 175, 410, 260, 320,
		325, 128, 52, 129, 412, 414, 428, 272, 386, 436, 386, 336, 436, 77, 79,
		215, 251, 217, 216, 437, 435, 325, 50, 52, 388, 324, 105, 325, 436,
		336, 258, 436, 258, 438, 435, 176, 175, 435, 177, 176, 325, 105, 437,
		316, 435, 437, 435, 316, 177, 272, 436, 370, 303, 370, 439, 439, 370,
		436, 328, 438, 258, 105, 316, 437, 336, 386, 334, 303, 440, 374, 303,
		439, 440, 436, 438, 439, 105, 133, 316, 328, 251, 216, 440, 439, 427,
		438, 328, 50, 326, 433, 276, 433, 275, 276, 328, 216, 221, 328, 221,
		50, 431, 285, 148, 433, 430, 275, 285, 146, 148, 414, 433, 428, 414,
		432, 433, 374, 440, 375, 427, 375, 440, };

void Bunny::draw() const
{
	glBegin(GL_TRIANGLES);
	{
		for (size_t i = 0; i < indicesv.size(); i++)
		{
			glNormal3fv(verticesv[indicesv[i]].normal);
			glVertex3fv(verticesv[indicesv[i]].position);
		}
	}
	glEnd();
}

Bunny::Bunny() :
	indices(0), vertices(0)
{
	indices = sizeof(index_data) / sizeof(index_data[0]);
	vertices = sizeof(vertex_data) / (3 * sizeof(vertex_data[0]));

	std::cout << "Hi! I'm a freakin\' Stanford Bunny composed of " << indices
			<< " indices and " << vertices << " vertices!" << std::endl;

	for (size_t i = 0; i < indices; ++i)
	{
		indicesv.push_back(index_data[i]);
	}
	for (size_t i = 0; i < vertices * 3; i += 3)
	{
		Vertex tmp(vertex_data[i], vertex_data[i + 1], vertex_data[i + 2]);
		verticesv.push_back(tmp);
	}
	calculate_normals();
	fix_scale();
}

void Bunny::calculate_normals()
{
	std::size_t i0, i1, i2;

	for (size_t i = 0; i < verticesv.size(); ++i)
		verticesv[i].normal = Vec3(0, 0, 0);

	// iterate over all triangles and add their normals to adjacent vertices
	for (size_t i = 0; i < indicesv.size(); i += 3)
	{
		i0 = indicesv[i + 0];
		i1 = indicesv[i + 1];
		i2 = indicesv[i + 2];

		Vec3 const& p1 = verticesv[i0].position;
		Vec3 const& p2 = verticesv[i1].position;
		Vec3 const& p3 = verticesv[i2].position;
		Vec3 normal = cross(p2 - p1, p3 - p1);

		verticesv[i0].normal -= normal;
		verticesv[i1].normal -= normal;
		verticesv[i2].normal -= normal;
	}

	// normalize all the normals
	for (size_t i = 0; i < verticesv.size(); ++i)
		verticesv[i].normal /= magnitude(verticesv[i].normal);
}

void Bunny::fix_scale()
{
	Vec3 lower_left = verticesv[0].position;
	Vec3 upper_right = verticesv[0].position;

	// calculate bounding box
	for (size_t v = 1; v < verticesv.size(); ++v)
	{
		Vec3& pos = verticesv[v].position;
		for (size_t i = 0; i < 3; ++i)
		{
			lower_left.data[i] = std::min(lower_left[i], pos[i]);
			upper_right.data[i] = std::max(upper_right[i], pos[i]);
		}
	}

	// find largest dimension and determine scale factor
	float factor = 0.0f;
	for (size_t i = 0; i < 3; ++i)
		factor = std::max(factor, upper_right[i] - lower_left[i]);

	factor = 2.f / factor;
	std::clog << "scale factor = " << factor << "\n";

	// determine scale offset
	Vec3 offset;
	for (size_t i = 0; i < 3; ++i)
		offset.data[i] = (lower_left[i] + upper_right[i]) * 0.5f;

	std::clog << "offset = (" << (offset | X) << ", " //
			<< (offset | Y) << ", " << (offset | Z) << ")" << std::endl;

	// scale the data
	for (size_t v = 0; v < verticesv.size(); ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			verticesv[v].position.data[i] -= offset[i];
			verticesv[v].position.data[i] *= factor;
		}
	}
}
