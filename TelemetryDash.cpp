#include "TelemetryDash.h"

TelemetryDash::TelemetryDash(QWidget* parent) : QWidget(parent) {
    ui.setupUi(this);
    initStylesheet();

    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText("📍 Enter location");
    locationEdit->setGeometry(40, 180, 680, 40);

    priorityCombo = new QComboBox(this);
    priorityCombo->addItems({"🔴 High", "🟡 Medium", "🟢 Low"});
    priorityCombo->setCurrentIndex(1);
    priorityCombo->setGeometry(40, 230, 330, 40);

    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"💼 Work", "🏠 Personal", "🛒 Shopping", "🚗 Travel"});
    categoryCombo->setGeometry(390, 230, 330, 40);

    ui.AddNewBtn->setGeometry(ui.AddNewBtn->x(), 290, ui.AddNewBtn->width(), ui.AddNewBtn->height());


    connect(ui.AddNewBtn, SIGNAL(clicked()), this, SLOT(SlotAddNewTask()));

    ui.NewTaskLineEdit->setText("Today, I want to...");
    ui.NewDateText->setText(QDate::currentDate().toString());
}

void TelemetryDash::initStylesheet() {

    QFile style("style_Generic.css");
    bool ok = style.open(QFile::ReadOnly);
    if(ok) {
        QString s = QString::fromLatin1(style.readAll());
        setStyleSheet(s);
    }
}


void TelemetryDash::SlotAddNewTask() {
    QString taskName = ui.NewTaskLineEdit->text();

    if(taskName == "Today, I want to..." || taskName.isEmpty()) {
        taskName = ui.NewTaskText->text();
        if(taskName.isEmpty() || taskName == "LETS GOOOOOOOOOO!!!") {
            taskName = "New Task";
        }
    }

    QString location = locationEdit->text();
    if(location.isEmpty()) location = "No location";

    QString priority = priorityCombo->currentText();
    QString category = categoryCombo->currentText();
    QString date = QDate::currentDate().toString();

    createNewTask(taskName, location, priority, category, date);

    ui.NewTaskLineEdit->setText("Today, I want to...");
    ui.NewTaskText->clear();
    ui.NewTaskText->setPlaceholderText("LETS GOOOOOOOOOO!!!");
    locationEdit->clear();
}

void TelemetryDash::createNewTask(QString taskName, QString location, QString priority, QString category, QString date) {


    QVBoxLayout* vMainLayout = qobject_cast<QVBoxLayout*>(ui.AllNewTasksContents->layout());
    QFrame* Hframe = new QFrame();
    Hframe->setFrameStyle(QFrame::StyledPanel);
    QHBoxLayout* newTask = new QHBoxLayout(Hframe);
    Hframe->setLayout(newTask);
    QFrame* Vframe = new QFrame();
    QVBoxLayout* taskDetails = new QVBoxLayout(Vframe);
    Vframe->setLayout(taskDetails);

    QLabel* titlelabel = new QLabel(tr("📋 Task #%1").arg(vMainLayout->count()));
    taskDetails->addWidget(titlelabel);

    QLabel* tasklabel = new QLabel("🎯 " + taskName);
    taskDetails->addWidget(tasklabel);

    QLabel* locationlabel = new QLabel("📍 " + location);
    taskDetails->addWidget(locationlabel);

    QLabel* prioritylabel = new QLabel(priority);
    taskDetails->addWidget(prioritylabel);

    QLabel* categorylabel = new QLabel(category);
    taskDetails->addWidget(categorylabel);

    QLabel* datelabel = new QLabel("📅 " + date);
    taskDetails->addWidget(datelabel);
    newTask->insertWidget(0, Vframe);
    QSpacerItem* spacer = new QSpacerItem(100, 100, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    newTask->insertSpacerItem(1, spacer);

    QPushButton* deleteBtn = new QPushButton("Delete");
    newTask->insertWidget(2, deleteBtn);
    deleteBtn->setProperty("CurrentTask", QVariant(QVariant::fromValue<QFrame*>(Hframe)));

    vMainLayout->insertWidget(vMainLayout->count() - 1, Hframe);
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(SlotDeleteTask()));

    {
        QVector<QString> colors = { "rgba(66, 165, 245,1.0)", "rgba(41, 182, 246,1.0)", "rgba(38, 198, 218,1.0)", "rgba(38, 166, 154,1.0)", "rgba(102, 187, 106,1.0)", "rgba(156, 204, 101,1.0)", "rgba(212, 225, 87,1.0)", "rgba(255, 238, 88,1.0)", "rgba(255, 202, 40,1.0)", "rgba(255, 167, 38,1.0)" };
        int randomVal = (((rand() % 50) % 100) % (colors.size() - 1));

        Hframe->setObjectName("NewTask");
        Hframe->setStyleSheet("#NewTask { border-radius: 10px; border: 1px solid black; background-color: " + colors[randomVal] + "; }");

        tasklabel->setObjectName("TaskName");
        tasklabel->setStyleSheet("#TaskName { font: bold 11pt black 'Verdana'; }");

        deleteBtn->setObjectName("DeleteBtn");
        deleteBtn->setStyleSheet("#DeleteBtn { color: white; background-color: #ff2264; border-color: #b91043; }  #DeleteBtn:hover{ background-color: #b91043; border-color: #ff2264; }");
    }

}


void TelemetryDash::SlotDeleteTask() {
    QPushButton* fromButton = (QPushButton*)sender();

    QVariant var;
    var = fromButton->property("CurrentTask");
    QFrame* taskHBox = qvariant_cast<QFrame*>(var);

    taskHBox->deleteLater();
    delete taskHBox;

}

