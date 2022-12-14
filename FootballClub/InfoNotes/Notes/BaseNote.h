#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "Enums/Enums.h"

class BaseNote : public QWidget{
    Q_OBJECT
public:
    BaseNote(QWidget *parent = nullptr);
    void setNoteViewType(const NOTE_VIEW_TYPE type);
    NOTE_VIEW_TYPE getNoteViewTytpe() const;
    virtual ~BaseNote() = default;
protected:
    unsigned recordId;
    QBoxLayout* globalLay = nullptr;
    QPushButton* modifyButton = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void modifyNoteView() = 0;
};


