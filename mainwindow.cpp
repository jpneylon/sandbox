#include <math.h>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parameters = new SimParams;
    parameters->numParticles = DEFAULT_NUM_PARTICLES;
    QString str;
    str.setNum(parameters->numParticles);
    ui->inputTotalEdit->setText(str);

    parameters->numObjects = DEFAULT_NUM_OBJECTS;
    str.setNum(parameters->numObjects);
    ui->inputObjectEdit->setText(str);

    parameters->numCells = DEFAULT_NUM_CELLS;
    str.setNum(parameters->numCells);
    ui->inputCellEdit->setText(str);

    parameters->oControl = 0;
    ui->objControlSpinner->setValue(parameters->oControl);
    ui->objControlSpinner->setMaximum(parameters->numObjects-1);

    int slider;
    parameters->object = new ObjectParams[parameters->numObjects];
    for (unsigned int p=0; p<parameters->numObjects; p++)
    {
        parameters->object[p].mode = parameters->object->O_CUBE;

        parameters->object[p].damping = 0.1f;
        str.setNum(parameters->object[p].damping);
        ui->objDampValue->setText(str);
        slider = parameters->object[p].damping * ui->objDampSlider->maximum();
        ui->objDampSlider->setValue(slider);

        parameters->object[p].elasticity = 0.5f;
        str.setNum(parameters->object[p].elasticity);
        ui->objElasticValue->setText(str);
        slider = parameters->object[p].elasticity * ui->objElasticSlider->maximum();
        ui->objElasticSlider->setValue(slider);

        parameters->object[p].rigidity = 0.0f;
        str.setNum(parameters->object[p].rigidity);
        ui->objRigidValue->setText(str);
        slider = parameters->object[p].rigidity * ui->objRigidSlider->maximum();
        ui->objRigidSlider->setValue(slider);

        parameters->object[p].poissonRatio = 0.5f;
        str.setNum(parameters->object[p].poissonRatio);
        ui->objPoissonValue->setText(str);
        slider = parameters->object[p].poissonRatio * ui->objPoissonSlider->maximum();
        ui->objPoissonSlider->setValue(slider);

        parameters->object[p].volumeRatio = 1.0f;
        str.setNum(parameters->object[p].volumeRatio);
        ui->objPoissonValue->setText(str);
        slider = 0.5f * (2.5f - parameters->object[p].volumeRatio) * ui->objPoissonSlider->maximum();
        ui->objPoissonSlider->setValue(slider);

        parameters->object[p].youngsModulus = 5.0f;
    }

    parameters->colliderMode = parameters->P_SPHERE;
    parameters->colorMode = parameters->C_RAINBOW;
    parameters->elasticMode = parameters->E_LINEAR;
    parameters->integrationMode = parameters->I_IMPLICIT;
    parameters->latticeMode = parameters->L_FULL;
    parameters->mouseMode = parameters->M_VIEW;
    parameters->renderMode = parameters->R_SPHERES;

    parameters->cCount = 1;
    parameters->cControl = 0;
    for (unsigned int c=0; c<10; c++)
    {
        parameters->cOuterRadius[c] = 0.1f;
        parameters->cInnerRadius[c] = 0.1f;
    }
    parameters->cPosition.x = -0.5f * parameters->worldSize - 2.0f * parameters->cOuterRadius[0];
    parameters->cPosition.y = 0.0f;
    parameters->cPosition.z = 0.0f;
    parameters->cOrientation.x = 0.f;
    parameters->cOrientation.y = 0.f;
    parameters->cOrientation.z = 1.f;
    parameters->cMass = 1000.f * 4.f * PI_F * powf( parameters->cOuterRadius[0], 3.f) / 3.f;

    parameters->initialParticleRadius = 0.5f * DEFAULT_PARTICLE_DIAMETER;
    parameters->particleRadius = parameters->initialParticleRadius;
    QString strRad;
    strRad.setNum( parameters->particleRadius );
    ui->particleRadValue->setText( strRad );

    parameters->particleSpacing = DEFAULT_PARTICLE_DIAMETER;
    QString strSpace;
    strSpace.setNum( parameters->particleSpacing );
    ui->particleSpaceValue->setText( strSpace );

    parameters->particleMass = 1000.f * powf(DEFAULT_PARTICLE_DIAMETER, 3.f);
    QString strMass;
    strMass.setNum( parameters->particleSpacing );
    ui->particleMassValue->setText( strMass );

    parameters->cellSize = 2 * parameters->initialParticleRadius * powf( (float)parameters->numParticles, 0.5f ) / (float)parameters->numCells;
    parameters->worldSize = parameters->cellSize * (float)parameters->numCells;
    QString strWorld;
    strWorld.setNum( parameters->worldSize );
    ui->cubeSizeValue->setText( strWorld );
    QString strCell;
    strCell.setNum( parameters->cellSize );
    ui->cubeCellValue->setText( strCell );

    parameters->oscillatorID = 0;
    parameters->oscillatorAxis = 0;
    parameters->oscillatorAmplitude = 0.f;
    parameters->oscillatorFrequency = 0.f;

    parameters->deltaTime = 0.1f;
    parameters->frameRate = 10.f;
    parameters->realTime = false;
    parameters->gravityScaler = 0.f;
    parameters->gravity.x = 0.f;
    parameters->gravity.y = 0.f;
    parameters->gravity.z = 0.f;
    parameters->damping = 0.98f;

    parameters->pSpring = 0.5f;
    parameters->pDrag = 0.02f;
    parameters->pShear = 0.02f;
    parameters->pAttract = 0.02f;

    parameters->systemStateChanged = false;
}

MainWindow::~MainWindow()
{
    delete [] parameters->object;
    delete parameters;
    delete ui;
}

void MainWindow::on_inputTotalEdit_returnPressed()
{
    bool isInteger = false;
    unsigned int value =ui->inputTotalEdit->text().toInt(&isInteger);
    if (isInteger)
    {
            parameters->numParticles = value;
            parameters->perParticles = parameters->numParticles / parameters->numObjects;
            QString str;
            str.setNum( parameters->perParticles );
            ui->inputPerEdit->setText( str );
            parameters->systemStateChanged = true;
    }
    else
    {
        qDebug() << "Please enter an integer number of total particles.";
    }
}

void MainWindow::on_inputObjectEdit_returnPressed()
{
    bool isInteger = false;
    unsigned int value =ui->inputObjectEdit->text().toInt(&isInteger);
    if (isInteger)
    {
            parameters->numObjects = value;
            parameters->perParticles = parameters->numParticles / parameters->numObjects;
            QString str;
            str.setNum( parameters->perParticles );
            ui->inputPerEdit->setText( str );

            delete [] parameters->object;
            parameters->oControl = 0;
            parameters->object = new ObjectParams[parameters->numObjects];
            for (unsigned int p=0; p<parameters->numObjects; p++)
            {
                parameters->object[p].mode = parameters->object->O_CUBE;
                parameters->object[p].damping = 0.1f;
                parameters->object[p].elasticity = 0.5f;
                parameters->object[p].rigidity = 0.0f;
                parameters->object[p].poissonRatio = 0.5f;
                parameters->object[p].volumeRatio = 1.0f;
                parameters->object[p].youngsModulus = 5.0f;
            }

            parameters->systemStateChanged = true;
    }
    else
    {
        qDebug() << "Please enter an integer number of objects.";
    }
}

void MainWindow::on_inputPerEdit_returnPressed()
{
    bool isInteger = false;
    unsigned int value =ui->inputPerEdit->text().toInt(&isInteger);
    if (isInteger)
    {
            parameters->perParticles = value;
            parameters->numParticles = parameters->perParticles * parameters->numObjects;
            QString str;
            str.setNum( parameters->numParticles );
            ui->inputTotalEdit->setText( str );
            parameters->systemStateChanged = true;
    }
    else
    {
        qDebug() << "Please enter an integer number of particles per object.";
    }
}

void MainWindow::on_inputCellEdit_returnPressed()
{
    bool isInteger = false;
    unsigned int value =ui->inputCellEdit->text().toInt(&isInteger);
    if (isInteger)
    {
            parameters->numCells = value;
            parameters->systemStateChanged = true;
    }
    else
    {
        qDebug() << "Please enter an integer number of cells along each dimension of the deformation space.";
    }
}

void MainWindow::on_oscIndexEdit_returnPressed()
{
    bool isInteger = false;
    unsigned int value =ui->oscIndexEdit->text().toInt(&isInteger);
    if (isInteger && value < parameters->numParticles)
    {
            parameters->oscillatorID = value;
    }
    else
    {
        qDebug() << "Please enter an integer less than total number of particles as oscillator index.";
    }
}
