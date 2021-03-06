#if defined(QTFIREBASE_ADMOB_ENABLED)

#ifndef QTADMMOBINTERSTITIAL_H
#define QTADMMOBINTERSTITIAL_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include "firebase/future.h"
#include "firebase/admob/interstitial_ad.h"


class QtAdmMobInterstitial : public QObject, public firebase::admob::InterstitialAd::Listener
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(bool isReady READ isReady NOTIFY ready)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)

    Q_OBJECT
public:
    /*
     * Constructor
     */
    explicit QtAdmMobInterstitial(QObject *parent = 0);

    /*
     * Destructor
     */
    ~QtAdmMobInterstitial();

    /*
     * Set interstitial id
     */
    void setUnitId(const QString& unitId);
    
    /*
     * Get interstitial id
     */
    QString unitId() const;

    /*
     * Show interstitial
     */
    Q_INVOKABLE void show();

    /*
     * Is initialization done
     */
    bool isReady();

    /*
     * Is banner loaded
     */
    bool isLoaded();
    
    /*
     * InterstitialAd::Listener method
     */
    virtual void OnPresentationStateChanged(firebase::admob::InterstitialAd* interstitial_ad,
                                            firebase::admob::InterstitialAd::PresentationState state);

signals:
    void unitIdChanged();
    void ready();
    void loaded();
    void loading();
    void closed();

private:
    void initialize(char* unitId);
    void cleanup();
    void load();
    static void onInitCompletionCallback(const firebase::Future<void>& future, void* userData);
    static void onLoadCompletionCallback(const firebase::Future<void>& future, void* userData);

private:
    firebase::admob::InterstitialAd* m_Interstitial;
    char* m_UnitId;
    bool m_IsVisible;
};

#endif // QTADMMOBINTERSTITIAL_H

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
