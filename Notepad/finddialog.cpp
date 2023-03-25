#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    lineEdit = new QLineEdit(this);
    caseCheckBox = new QCheckBox(tr("Match case"), this);
    backwardCheckBox = new QCheckBox(tr("Search backward"), this);
    findButton = new QPushButton(tr("Find"), this);
    closeButton = new QPushButton(tr("Close"), this);

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableFindButton(const QString &)));
    connect(findButton, SIGNAL(clicked()),
            this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(lineEdit);
    topLayout->addWidget(findButton);
    topLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(caseCheckBox);
    mainLayout->addWidget(backwardCheckBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}
