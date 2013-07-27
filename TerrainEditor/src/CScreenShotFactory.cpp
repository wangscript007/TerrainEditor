/* 
 * File:   CScreenShotFactory.cpp
 * Author: hokan
 * 
 * Created on 25 Июль 2013 г., 0:04
 */

#include "../headers/CScreenShotFactory.h"

namespace irr {

    /**
     * Constructor
     * 
     * @param pDevice        pointer to IrrlichtDevice
     * @param templateName  file name templates
     */
    CScreenShotFactory::CScreenShotFactory(IrrlichtDevice* pDevice, const c8* templateName)
    : pDevice(pDevice), screenShotNumber(0), filenameTemplate(templateName) {
        filenameTemplate.replace('/', '_');
        filenameTemplate.replace('\\', '_');
    }

    /**
     * Operates events producing new screenshots (pressing F9 button)
     * 
     * @param event incomming event
     * @return true if incomming event processed
     */
    bool CScreenShotFactory::OnEvent(const SEvent& event) {
        // check if user presses the key print screen
        if ((event.EventType == EET_KEY_INPUT_EVENT) && event.KeyInput.PressedDown) {
            if (event.KeyInput.Key == KEY_F9) {
                video::IImage* image = pDevice->getVideoDriver()->createScreenShot();
                if (image) {
                    core::stringw screenShotFileName = filenameTemplate.c_str();
                    screenShotFileName += ++screenShotNumber;
                    screenShotFileName += ".jpg";
                    pDevice->getVideoDriver()->writeImageToFile(image, screenShotFileName, 85);
                    image->drop();
                }
            }
        }
        return false;
    }
} // end of namespace irr


