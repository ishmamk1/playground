from flask import Flask, send_file
import cv2
import io

app = Flask(__name__)

@app.route("/screenshot")
def camera_snapshot():
    cap = cv2.VideoCapture(0)  # 0 is the default camera
    ret, frame = cap.read()
    cap.release()

    if not ret:
        return "Failed to grab frame", 500

    # Encode image as PNG in memory
    _, buffer = cv2.imencode('.png', frame)
    img_io = io.BytesIO(buffer.tobytes())
    img_io.seek(0)

    return send_file(img_io, mimetype='image/png')

app.run(host="0.0.0.0", port=5001)

