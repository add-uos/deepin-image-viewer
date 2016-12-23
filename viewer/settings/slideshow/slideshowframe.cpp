#include "slideshowframe.h"
#include "slideshowpreview.h"
#include "application.h"
#include "controller/configsetter.h"
#include "../title.h"
#include <dsimplecombobox.h>
#include <dthememanager.h>
#include <QHBoxLayout>
#include <QStyleFactory>
#include <QPushButton>
#include <QVBoxLayout>

namespace {

const QString DURATION_SETTING_GROUP = "SLIDESHOWDURATION";
const QString DURATION_SETTING_KEY = "Duration";

}

using namespace Dtk::Widget;

SlideshowFrame::SlideshowFrame(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 20, 0, 0);
    m_layout->setSpacing(0);

    Title1 *tl1 = new Title1(tr("Slideshow"));
    m_layout->addWidget(tl1);

    initPreview();
    initInterval();
}

int SlideshowFrame::defaultDuration() const
{
    QVariant v = dApp->setter->value(DURATION_SETTING_GROUP, DURATION_SETTING_KEY);
    if (v.isNull()) {
        dApp->setter->setValue(DURATION_SETTING_GROUP, DURATION_SETTING_KEY, 1);
        return 1;
    }
    else {
        return v.toInt();
    }
}

void SlideshowFrame::initPreview()
{

    // Preview
    Title2 *tlEffect = new Title2(tr("Switch effect"));
    m_layout->addSpacing(10);
    m_layout->addWidget(tlEffect);

    QHBoxLayout *previewLayout = new QHBoxLayout;
    previewLayout->setContentsMargins(0, 0, 0, 0);
    previewLayout->setSpacing(7);
    previewLayout->addStretch();
    previewLayout->addWidget(new SlideshowPreview(SlideshowPreview::Blinds));
    previewLayout->addWidget(new SlideshowPreview(SlideshowPreview::Slide));
    previewLayout->addWidget(new SlideshowPreview(SlideshowPreview::Switcher));
    previewLayout->addWidget(new SlideshowPreview(SlideshowPreview::Circle));
    previewLayout->addStretch();
    m_layout->addSpacing(16);
    m_layout->addLayout(previewLayout);
}

void SlideshowFrame::initInterval()
{
    // Duration
    Title2 *tlDuration = new Title2(tr("Duration"));
    m_layout->addSpacing(20);
    m_layout->addWidget(tlDuration);

    QHBoxLayout *timeLayout = new QHBoxLayout;
    timeLayout->setContentsMargins(0, 0, 0, 0);
    timeLayout->setSpacing(103);
    timeLayout->addSpacing(37);
    timeLayout->addWidget(new Title3(tr("Switch duration")));

    QSignalBlocker blocker(DThemeManager::instance());
    Q_UNUSED(blocker);
//    DThemeManager::instance()->setTheme("light");
    DSimpleComboBox *dcb = new DSimpleComboBox(this);
//    DThemeManager::instance()->setTheme("dark");
//    dcb->setStyle(QStyleFactory::create("dlight"));
    dcb->setFixedSize(238, 26);
    QStringList intervalList;
    for (int i = 2; i < 6; i ++){
        intervalList << QString::number(i) + " " + tr("second");
    }
    dcb->addItems(intervalList);
    dcb->setEditable(false);
    dcb->setCurrentIndex(defaultDuration() - 1);
    connect(dcb, &DSimpleComboBox::currentTextChanged,
            this, [=] (const QString &text) {
        int i = QString(text.split(" ").first()).toInt();
        if (i != 0) {
            dApp->setter->setValue(DURATION_SETTING_GROUP, DURATION_SETTING_KEY, i);
        }
    });

    timeLayout->addWidget(dcb);
    timeLayout->addStretch();
    m_layout->addSpacing(10);
    m_layout->addLayout(timeLayout);

    m_layout->addStretch();

}