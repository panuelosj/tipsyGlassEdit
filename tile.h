//=============================================================================
//-------------------------DEFINES---------------------------------------------
//=============================================================================
#define TYPE_HEADER 1
#define TYPE_GAS 2
#define TYPE_DARK 3
#define TYPE_STAR 4
#define VAL_NaN 3.402823466e+38
#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

#define ERR_MALLOC_FAIL 1
#define ERR_FILE_OPEN 2
#define ERR_NO_PARTICLES 3

//=============================================================================
//-------------------------TYPEDEF STUFFS--------------------------------------
//=============================================================================

typedef struct {
    double simtime;
    int nbodies;
    int ndim;
    int nsph;
    int ndark;
    int nstar;
    int pad;
} header;
typedef struct {
    float mass;
    float pos[3];
    float vel[3];
    float rho;
    float temp;
    float eps;
    float metals;
    float phi;
} gas_particle;
typedef struct {
    float mass;
    float pos[3];
    float vel[3];
    float eps;
    float phi;
} dark_particle;
typedef struct {
    float mass;
    float pos[3];
    float vel[3];
    float metals;
    float tform;
    float eps;
    float phi;
} star_particle;
typedef struct{
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    float zmin;
    float zmax;
    int nloadedsph;     // number of particles currently loaded (not VAL_NaN)
    int nloadeddark;
    int nloadedstar;
} attributes;
typedef struct {
    header* header;
    gas_particle* gas;
    dark_particle* dark;
    star_particle* star;
    attributes* attr;
} tipsy;

//=============================================================================
//-------------------------FUNCTION PROTOTYPES---------------------------------
//=============================================================================

// tileCalc.c
tipsy* tipsyCompress(tipsy* tipsyIn, const float xCompress, const float yCompress, const float zCompress);
void tipsyTesselate(tipsy* tipsyIn, const int xTile, const int yTile, const int ztile);
void tipsyScaleShrink(tipsy* tipsyIn, const int xShrink, const int yShrink, const int zShrink);
void autoFindBounds(tipsy* tipsyIn);

// tileStructEdit.c
tipsy* createTipsy(const double simtime, const int nsph, const int ndark, const int nstar);
tipsy* tipsyClone(tipsy* tipsyIn);


// tileFileIO.c
tipsy* readTipsyStd(const char filename[]);
int writeTipsyStd(const char filename[], tipsy* tipsyOut);

// tileMisc.c
void errorCase(const int errorCode);
int swapEndianInt(const int valIn);
double swapEndianDouble(const double valIn);
float swapEndianFloat(const float valIn);
void swapEndianBatch(const tipsy* tipsyIn, const int type, const int i);

// tile.c
void printGas(gas_particle* p);
void printHeader(header* h);
