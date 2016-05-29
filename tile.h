//=============================================================================
//-------------------------DEFINES---------------------------------------------
//=============================================================================
#define TYPE_HEADER 1
#define TYPE_GAS 2
#define TYPE_DARK 3
#define TYPE_STAR 4
#define VAL_NaN 3.402823466e+38

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
typedef struct {
    header* header;
    gas_particle* gas;
    dark_particle* dark;
    star_particle* star;
} tipsy;

//=============================================================================
//-------------------------FUNCTION PROTOTYPES---------------------------------
//=============================================================================

// tileFileIO.c
tipsy* readTipsyStd(const char filename[]);
int writeTipsyStd(const char filename[], tipsy* tipsyOut);

// tileMisc.c
tipsy* createTipsy(const double simtime, const int nsph, const int ndark, const int nstar);

int swapEndianInt(const int valIn);
double swapEndianDouble(const double valIn);
float swapEndianFloat(const float valIn);
void swapEndianBatch(const tipsy* tipsyIn, const int type, const int i);

// tile.c
void printGas(gas_particle* p);
void printHeader(header* h);
