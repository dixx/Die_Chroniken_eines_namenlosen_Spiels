/*! \file Camera.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Kameras bereit.
 */

#ifndef _CAMERA_HEADER
#define _CAMERA_HEADER

#include <irrlicht.h>

using namespace irr;

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
    static Camera& getInstance( scene::ISceneManager* sceneManager = 0 );

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
    void rotate( const f32 value );

    /*! \brief Spielrelevante Werte der Kamera werden gesetzt.
     *  \param frameDeltaTime (\a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void update( const f32 frameDeltaTime );

    /*! \brief Bindet die Kamera an einen anderen Szenenknoten.
     *  \param node (\a scene::ISceneNode*) Knoten dem die Kamera folgen soll
     *  \return -
     */
    void followNode( scene::ISceneNode* node );

#ifdef _DEBUG_MODE
    void toggleSpeed();
    core::vector3df& getCurrentPosition();
#endif

private:

    scene::ISceneManager* smgr_;
    scene::ICameraSceneNode* firstCameraNode_;
    //scene::ICameraSceneNode* secondCameraNode_;
    scene::ISceneNode* lockNode_;
    core::vector3df currentTarget_;
    core::vector3df targetOffset_;
    core::vector3df currentPosition_;
    core::vector3df positionOffset_;
    f32 speed_;
    f32 zoomingSpeed_;
    f32 desiredPositionOffsetHeight_;
    f32 zoomMin_;
    f32 zoomMax_;
    bool isZooming_;
    enum zoom { ZOOM_IN, ZOOM_OUT };
    zoom zoomDirection_;
    f32 groundHeight_;  // wegen Performance
    f32 dummySum_;  // wegen Performance

    Camera( scene::ISceneManager* sceneManager );
    Camera( const Camera& );
    Camera& operator=( const Camera& );
    ~Camera();

    inline void changeZoom( const f32 frameDeltaTime );
    inline void liftCameraToKeepTargetVisible();

};

#endif
