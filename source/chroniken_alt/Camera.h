/*! \file Camera.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Kameras bereit.
 */

#ifndef _CAMERA_HEADER
#define _CAMERA_HEADER

#include <irrlicht.h>

/*! \class Camera Camera.h "Camera.h"
 *  \brief  Schnittstelle zu Kameras.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Camera& myCamera = Camera::getInstance();`\n Oder: `Camera::getInstance();`
 *        \n Benutzen: `myCamera.startZoomingIn();`\n Oder: `Camera::getInstance().startZoomingOut();`
 */
class Camera
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param sceneManager (\a scene::ISceneManager*) Zeiger auf den aktuellen SzenenManager des Entchens
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Camera& getInstance( irr::scene::ISceneManager* sceneManager = 0 );

    /*! \brief Kamera beginnt AutoZoom nach unten.
     *  \return -
     */
    void startZoomingIn();

    /*! \brief Kamera beginnt AutoZoom nach oben.
     *  \return -
     */
    void startZoomingOut();

    /*! \brief Dreht das Kamera-Offset um die Kamera-Position.
     *  \param value (\a f32) FrameDeltaTime benutzen, Vorzeichen beachten!
     *  \return -
     */
    void rotate( const irr::f32 value );

    /*! \brief Spielrelevante Werte der Kamera werden gesetzt.
     *  \param frameDeltaTime (\a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void update( const irr::f32 frameDeltaTime );

    /*! \brief Bindet die Kamera an einen anderen Szenenknoten.
     *  \param node (\a scene::ISceneNode*) Knoten dem die Kamera folgen soll
     *  \return -
     */
    void followNode( irr::scene::ISceneNode* node );

#ifdef _DEBUG_MODE
    void toggleSpeed();
    irr::core::vector3df& getCurrentPosition();
#endif

private:

    irr::scene::ISceneManager* smgr_;
    irr::scene::ICameraSceneNode* firstCameraNode_;
    //scene::ICameraSceneNode* secondCameraNode_;
    irr::scene::ISceneNode* lockNode_;
    irr::core::vector3df currentTarget_;
    irr::core::vector3df targetOffset_;
    irr::core::vector3df currentPosition_;
    irr::core::vector3df positionOffset_;
    irr::f32 speed_;
    irr::f32 zoomingSpeed_;
    irr::f32 desiredPositionOffsetHeight_;
    irr::f32 zoomMin_;
    irr::f32 zoomMax_;
    bool isZooming_;
    enum zoom { ZOOM_IN, ZOOM_OUT };
    zoom zoomDirection_;
    irr::f32 groundHeight_;  // wegen Performance
    irr::f32 dummySum_;  // wegen Performance

    Camera( irr::scene::ISceneManager* sceneManager );
    Camera( const Camera& );
    Camera& operator=( const Camera& );
    ~Camera();

    inline void changeZoom( const irr::f32 frameDeltaTime );
    inline void liftCameraToKeepTargetVisible();

};

#endif
