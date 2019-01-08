{-# language DataKinds #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent (forkIO)
import Control.Monad (forever, liftM)
import Data.ByteString (ByteString)
import Data.ByteString.Lazy (fromStrict)
import Data.IORef (atomicWriteIORef, IORef, newIORef, readIORef)
import GHC.Word (Word8)
import Linear.V2 (V2(..))
import OpenCV
import OpenCV.VideoIO.Types
import qualified Web.Scotty as SC

type ImageD = Mat ('S ['D, 'D]) 'D 'D
type ImageS = Mat ('S ['D, 'D]) ('S 3) ('S Word8)

openCam :: IO (Maybe VideoCapture)
openCam = do
    cap <- newVideoCapture
    exceptErrorIO $ videoCaptureOpen cap $ VideoDeviceSource 0 Nothing
    isOpened <- videoCaptureIsOpened cap
    case isOpened of
        False -> return Nothing
        True -> videoCaptureSetD cap VideoCapPropFps 5 >> (return $ Just cap)

captureCam :: VideoCapture -> IO (Maybe ImageD)
captureCam cap = videoCaptureGrab cap >> videoCaptureRetrieve cap 

imgToPng :: ImageD -> ByteString
imgToPng = exceptError . imencode (OutputPng defaultPngParams)

main :: IO ()
main = do
    capMaybe <- openCam
    case capMaybe of
        Nothing -> putStrLn "couldn't open device"
        Just cap -> do
            Just png0 <- liftM imgToPng <$> captureCam cap
            pngRef <- newIORef png0
            _ <- forkIO $ runCam cap pngRef
            runServer 3000 pngRef

runServer :: Int -> IORef ByteString -> IO ()
runServer port pngRef = SC.scotty port $ do
    SC.get "/" $ SC.file "index.html"
    SC.get "/out.png" $ do
        SC.setHeader "Content-Type" "image/png"
        img <- SC.liftAndCatchIO (readIORef pngRef) 
        SC.raw $ fromStrict img

runCam :: VideoCapture -> IORef ByteString -> IO ()
runCam cap pngRef = forever $ do
    imgMaybe <- liftM imgToPng <$> captureCam cap
    maybe (return ()) (atomicWriteIORef pngRef) imgMaybe

