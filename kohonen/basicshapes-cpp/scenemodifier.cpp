/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scenemodifier.h"

#include <QtCore/QDebug>


SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity,float _z,float _x, float _y)
    : m_rootEntity(rootEntity)
{
    this->z=_z;
    this->x=_x;
    this->y=_y;
    vector<vector<vector<Qt3DExtras::QSphereMesh  *>>>_sphereMesh(z,vector<vector<Qt3DExtras::QSphereMesh  *>>(x,vector<Qt3DExtras::QSphereMesh  *> (y)));
    vector<vector<vector<Qt3DCore::QTransform *>>> _sphereTransform(z,vector<vector<Qt3DCore::QTransform *>>(x,vector<Qt3DCore::QTransform *> (y)));
    vector<vector<vector<Qt3DExtras::QPhongMaterial *>>> _sphereMaterial(z,vector<vector<Qt3DExtras::QPhongMaterial *>>(x,vector<Qt3DExtras::QPhongMaterial *> (y)));
    for(unsigned k=0;k<z;++k){
        for(unsigned i=0;i<x;++i){
            for(unsigned j=0;j<y;++j){
                _sphereMesh[k][i][j] = new Qt3DExtras::QSphereMesh();
                _sphereMesh[k][i][j]->setRings(20);
                _sphereMesh[k][i][j]->setSlices(20);
                _sphereMesh[k][i][j]->setRadius(2);

                _sphereTransform[k][i][j] = new Qt3DCore::QTransform();

                _sphereTransform[k][i][j]->setScale(1.3f);
                _sphereTransform[k][i][j]->setTranslation(QVector3D(-5.0f+(i*7), -5.0f +(j*7), 0.0f-(k*7)));

                _sphereMaterial[k][i][j] = new Qt3DExtras::QPhongMaterial();
                _sphereMaterial[k][i][j]->setDiffuse(QColor(255,255,255,0));

            }
        }
    }
    this->sphereMesh=_sphereMesh;
    this->sphereMaterial=_sphereMaterial;
    this->sphereTransform=_sphereTransform;
}

void SceneModifier::Dibujar(Qt3DCore::QEntity *rootEntity)
{
    for(unsigned k=0;k<z;++k){
        for(unsigned i=0;i<x;++i){
            for(unsigned j=0;j<y;++j){
                m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
                m_sphereEntity->addComponent(this->sphereMesh[k][i][j]);
                m_sphereEntity->addComponent(this->sphereMaterial[k][i][j]);
                m_sphereEntity->addComponent(this->sphereTransform[k][i][j]);
            }
        }
    }
}

void SceneModifier::CambiarC(Qt3DCore::QEntity *rootEntity,int _x ,int _y, int _z)
{

    sphereMaterial[_z][_x][_y]->setDiffuse(QColor(255,0,0,0));
    m_sphereEntity->addComponent(this->sphereMaterial[_z][_y][_x]);

}

SceneModifier::~SceneModifier()
{
}

//! [4]

void SceneModifier::enableSphere(bool enabled)
{
    m_sphereEntity->setParent(enabled ? m_rootEntity : nullptr);
}
