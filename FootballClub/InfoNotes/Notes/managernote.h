#ifndef MANAGERNOTE_H
#define MANAGERNOTE_H

#include "BaseNote.h"

class ManagerNote : public BaseNote
{
public:
    ManagerNote();

    void setNoteViewType(const NOTE_VIEW_TYPE type) override;
    void extend() override;
    void setStyles() override;

    void saveDataBeforeAction() override;
    void setAllDataOnLayout() override;
    void insertFieldsInMap() override;
    void transformNoteInLabelView() override;

    void setTeamTypesComboList(QSqlQuery& query) override;
    void setManagerTitleComboList(QSqlQuery& query) override;
    void setCountryComboList(QSqlQuery& query) override;

private slots:
    void modifyNoteView() override;
    void onSaveChangesClicked();
    void onCancelModifyingClicked();
    void onDeleteButtonClicked();
};

#endif // MANAGERNOTE_H
