#ifndef BREEZE_DECORATION_H
#define BREEZE_DECORATION_H

/*
 * Copyright 2014  Martin Gräßlin <mgraesslin@kde.org>
 * Copyright 2014  Hugo Pereira Da Costa <hugo.pereira@free.fr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "breezecolorsettings.h"
#include "breeze.h"
#include "breezesettings.h"

#include <KDecoration2/Decoration>

#include <QPalette>
#include <QPropertyAnimation>
#include <QVariant>

namespace KDecoration2
{
    class DecorationButton;
    class DecorationButtonGroup;
}

namespace Breeze
{
    class SizeGrip;
    class Decoration : public KDecoration2::Decoration
    {
        Q_OBJECT

        //* declare active state opacity
        Q_PROPERTY( qreal opacity READ opacity WRITE setOpacity )

        public:

        //* constructor
        explicit Decoration(QObject *parent = nullptr, const QVariantList &args = QVariantList());

        //* destructor
        virtual ~Decoration();

        //* paint
        void paint(QPainter *painter, const QRect &repaintRegion) override;

        //* color settings
        const ColorSettings &colorSettings()
        { return m_colorSettings; }

        //* internal settings
        const InternalSettings &internalSettings()
        { return m_internalSettings; }

        //* caption height
        int captionHeight() const;

        //* button height
        int buttonHeight() const;

        //*@name active state change animation
        //@{
        void setOpacity( qreal value )
        {
            if( m_opacity == value ) return;
            m_opacity = value;
            update();
        }

        qreal opacity( void ) const
        { return m_opacity; }

        //@}


        //*@name colors
        //@{
        QColor titleBarColor( void ) const;
        QColor outlineColor( void ) const;
        QColor fontColor( void ) const;
        //@}

        public Q_SLOTS:
        void init() override;

        private Q_SLOTS:
        void reconfigure();
        void recalculateBorders();
        void updateButtonPositions();
        void updateTitleBar();
        void updateAnimationState();

        private:
        QRect captionRect() const;

        void createButtons();
        void paintTitleBar(QPainter *painter, const QRect &repaintRegion);
        void createShadow();

        //*@name size grip
        //@{

        void createSizeGrip( void );
        void deleteSizeGrip( void );
        SizeGrip* sizeGrip( void ) const
        { return m_sizeGrip; }

        //@}

        ColorSettings m_colorSettings;
        InternalSettings m_internalSettings;

        QList<KDecoration2::DecorationButton*> m_buttons;
        KDecoration2::DecorationButtonGroup *m_leftButtons;
        KDecoration2::DecorationButtonGroup *m_rightButtons;

        //* size grip widget
        SizeGrip *m_sizeGrip;

        //* active state change animation
        QPropertyAnimation *m_animation;

        //* active state change opacity
        qreal m_opacity = 0;

    };

}

#endif