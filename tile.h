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
int swapEndianInt(const int valIn);
double swapEndianDouble(const double valIn);
float swapEndianFloat(const float valIn);

// tile.c
void printGas(gas_particle* p);
void printHeader(header* h);
