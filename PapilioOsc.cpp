#include "PapilioOsc.h"

const short int wavetable[600]={137,679,1228,1785,2355,2941,3546,4170,4812,5469,6137,6811,7490,8169,8845,9516,10178,10829,11465,12086,12690,13275,13840,14383,14904,15402,15875,16324,16748,17147,17522,17874,18203,18512,18801,19070,19322,19556,19774,19976,20164,20338,20498,20646,20782,20906,21020,21124,21219,21305,21382,21451,21514,21569,21617,21659,21695,21725,21749,21768,21782,21792,21797,21798,21796,21792,21785,21776,21766,21755,21743,21731,21719,21707,21695,21684,21673,21663,21652,21642,21632,21621,21609,21596,21581,21564,21543,21520,21494,21466,21437,21408,21378,21349,21320,21291,21261,21230,21197,21163,21128,21092,21056,21019,20984,20949,20916,20884,20854,20826,20799,20773,20748,20725,20702,20680,20659,20639,20621,20603,20588,20574,20562,20552,20543,20536,20529,20524,20520,20516,20513,20511,20509,20508,20508,20508,20509,20510,20512,20514,20516,20518,20520,20522,20524,20525,20526,20527,20528,20528,20528,20527,20526,20525,20523,20520,20517,20514,20509,20504,20498,20492,20485,20477,20469,20460,20451,20442,20433,20423,20413,20402,20391,20379,20366,20352,20338,20323,20307,20291,20275,20258,20242,20227,20213,20200,20188,20178,20170,20163,20156,20150,20144,20138,20133,20128,20124,20120,20118,20115,20112,20110,20107,20103,20098,20093,20086,20077,20068,20056,20042,20026,20008,19987,19963,19935,19903,19867,19827,19781,19730,19672,19609,19538,19461,19376,19283,19181,19071,18950,18818,18675,18520,18352,18169,17971,17756,17525,17278,17016,16741,16455,16158,15850,15531,15200,14854,14493,14116,13725,13319,12900,12468,12022,11565,11095,10616,10129,9637,9141,8641,8140,7636,7131,6624,6118,5612,5109,4612,4121,3641,3171,2708,2247,1783,1311,820,267,-354,-979,-1585,-2168,-2722,-3247,-3741,-4205,-4640,-5047,-5429,-5791,-6135,-6461,-6768,-7056,-7326,-7578,-7815,-8037,-8245,-8440,-8622,-8795,-8959,-9116,-9267,-9411,-9548,-9679,-9803,-9920,-10033,-10143,-10250,-10355,-10459,-10562,-10665,-10768,-10872,-10976,-11083,-11193,-11307,-11426,-11550,-11682,-11820,-11967,-12121,-12283,-12453,-12630,-12813,-13002,-13196,-13394,-13595,-13799,-14006,-14213,-14421,-14629,-14837,-15043,-15247,-15449,-15647,-15841,-16032,-16220,-16404,-16587,-16768,-16948,-17128,-17308,-17490,-17674,-17860,-18048,-18237,-18427,-18617,-18807,-18996,-19182,-19365,-19543,-19717,-19886,-20048,-20203,-20352,-20493,-20626,-20752,-20870,-20980,-21084,-21180,-21270,-21354,-21433,-21508,-21577,-21643,-21705,-21763,-21818,-21869,-21917,-21963,-22005,-22045,-22083,-22118,-22151,-22182,-22211,-22238,-22264,-22288,-22310,-22330,-22348,-22365,-22381,-22394,-22406,-22417,-22426,-22433,-22439,-22444,-22447,-22448,-22448,-22448,-22445,-22442,-22437,-22431,-22424,-22416,-22406,-22396,-22385,-22373,-22359,-22345,-22330,-22314,-22297,-22279,-22261,-22241,-22220,-22199,-22176,-22152,-22128,-22101,-22074,-22045,-22015,-21983,-21949,-21914,-21878,-21839,-21798,-21754,-21707,-21658,-21605,-21550,-21491,-21429,-21364,-21297,-21226,-21153,-21076,-20996,-20913,-20826,-20735,-20639,-20539,-20435,-20326,-20212,-20095,-19973,-19848,-19720,-19587,-19451,-19310,-19166,-19018,-18866,-18709,-18549,-18385,-18218,-18047,-17872,-17694,-17514,-17330,-17143,-16953,-16760,-16565,-16367,-16167,-15965,-15761,-15557,-15352,-15146,-14941,-14736,-14532,-14330,-14129,-13931,-13736,-13545,-13359,-13180,-13008,-12844,-12689,-12542,-12403,-12275,-12157,-12051,-11958,-11878,-11809,-11747,-11690,-11637,-11586,-11539,-11498,-11463,-11438,-11422,-11415,-11416,-11426,-11442,-11465,-11494,-11529,-11568,-11612,-11659,-11708,-11760,-11813,-11868,-11924,-11982,-12040,-12098,-12156,-12211,-12263,-12310,-12353,-12390,-12422,-12446,-12463,-12473,-12473,-12464,-12445,-12416,-12374,-12319,-12249,-12162,-12056,-11928,-11771,-11575,-11295,-10936,-10557,-10174,-9790,-9409,-9029,-8652,-8278,-7905,-7531,-7157,-6781,-6402,-6019,-5632,-5240,-4842,-4439,-4029,-3615,-3198,-2775,-2339,-1885,-1409,-913,-396,};


Osc::Osc()
{
  input_waveform = 0;
  input_volume = 255;
  ulPhaseIncrement = 220*TICKS_PER_CYCLE;
  ulPhaseAccumulator = 0;
}

long Osc::output()
{
  ulPhaseAccumulator += ulPhaseIncrement;   
  if(ulPhaseAccumulator > SAMPLES_PER_CYCLE_FIXEDPOINT) 
  { 
    ulPhaseAccumulator -= SAMPLES_PER_CYCLE_FIXEDPOINT; 
  } 
  return (wavetable[ulPhaseAccumulator>>20]*input_volume)>>8;
}

void Osc::updateParam(long input_freq)
{
  ulPhaseIncrement = input_freq*TICKS_PER_CYCLE; 
  
}
