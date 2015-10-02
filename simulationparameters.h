#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#define PI_F                                                            3.14159f
#define DEFAULT_NUM_PARTICLES            32768
#define DEFAULT_NUM_CELLS                      256
#define DEFAULT_NUM_OBJECTS                1
#define MAX_COLLIDER_COUNT                  10
#define DEFAULT_PARTICLE_DIAMETER   0.005f
#define ACCEL_GRAV                                         9.80665f


struct float3
{
    float x;
    float y;
    float z;
};

struct ObjectParams
{
    enum { O_CUBE = 0, O_PYRAMID, O_SHEET };
    unsigned int mode;

    float damping;
    float youngsModulus;
    float poissonRatio;
    float volumeRatio;
    float rigidity;
    float elasticity;
};


class SimParams
{
public:
    unsigned int numParticles;
    unsigned int numObjects;
    unsigned int perParticles;
    unsigned int numCells;

    unsigned int oControl;
    ObjectParams *object;

    float worldSize;
    float cellSize;

    float initialParticleRadius;
    float particleRadius;
    float particleSpacing;
    float particleMass;

    unsigned int oscillatorID;
    unsigned int oscillatorAxis;
    float oscillatorAmplitude;
    float oscillatorFrequency;

    float deltaTime;
    float frameRate;
    bool realTime;
    float gravityScaler;
    float3 gravity;
    float damping;

    float pSpring;
    float pDrag;
    float pShear;
    float pAttract;

    float3 cPosition;
    float3 cOrientation;
    float cMass;
    unsigned int cCount;
    unsigned int cControl;
    float cOuterRadius[MAX_COLLIDER_COUNT];
    float cInnerRadius[MAX_COLLIDER_COUNT];

    enum { P_SPHERE = 0, P_TORUS, P_CYLINDER };
    unsigned int colliderMode;

    enum { M_VIEW = 0, M_COLLIDER, M_OBJECT, M_OSCILLATOR };
    unsigned int mouseMode;

    enum { E_LINEAR = 0, E_HYBRID, E_HYPER };
    unsigned int elasticMode;

    enum { I_IMPLICIT = 0, I_IMPROVED };
    unsigned int integrationMode;

    enum { C_RAINBOW = 0, C_DEFORM, C_FORCE };
    unsigned int colorMode;

    enum { L_FULL = 0, L_CARDINAL, L_ORDINAL };
    unsigned int latticeMode;

    enum { R_SPHERES = 0, R_POINTS, R_SPRINGS };
    unsigned int renderMode;

    bool systemStateChanged;
};


#endif // SIMULATIONPARAMETERS_H

