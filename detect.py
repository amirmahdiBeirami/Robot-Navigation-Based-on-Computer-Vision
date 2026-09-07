import cv2
import os
import numpy as np
import torch
import tensorflow as tf
import sys

# Add the local YOLOv5 repository to the system path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), 'yolov5')))

# Import the YOLOv5 model from the local repository
from yolov5.models.experimental import attempt_load
from yolov5.utils.general import non_max_suppression
from yolov5.utils.torch_utils import select_device

# Load the YOLOv5 model for detection
device = select_device('')  # Use '' for auto-selection (CPU/GPU)
yolo_model = attempt_load('../Model/weights/best.pt', device=device)  # Adjust path to your YOLO weights
yolo_model.eval()  # Set to evaluation mode

# Load the TFLite model for classification
model_path = '../Model/traffic_sign_classifier_final.tflite'
interpreter = tf.lite.Interpreter(model_path=model_path)
interpreter.allocate_tensors()

# Get input and output tensor details for TFLite
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Define your class names for the CNN model
classes = [
    "Speed limit (30km/h)",
    "Speed limit (60km/h)",
    "Stop",
    "Go straight",
    "Go Left",
    "Go Right",
    "Background/No Sign"
]

# Set confidence threshold for detections
conf_threshold = 0.5

# Initialize webcam
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Error: Could not open webcam.")
    exit()

print("Press 'q' to quit.")

while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: Failed to capture frame.")
        break

    # Prepare image for YOLOv5
    img = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    img = torch.from_numpy(img).to(device).float()
    img /= 255.0  # Normalize
    if img.ndimension() == 3:
        img = img.permute(2, 0, 1).unsqueeze(0)  # Add batch dimension and reorder to (batch, channels, height, width)

    # Perform detection with YOLOv5
    with torch.no_grad():
        pred = yolo_model(img)[0]
    pred = non_max_suppression(pred, conf_thres=conf_threshold, iou_thres=0.45)

    # Process each detection
    for det in pred:
        if det is not None and len(det):
            for *xyxy, conf, _ in det:  # Ignore YOLO class, use CNN for classification
                x1, y1, x2, y2 = map(int, xyxy)
                if conf > conf_threshold:
                    # Crop the detected region
                    crop = frame[y1:y2, x1:x2]
                    if crop.shape[0] > 0 and crop.shape[1] > 0:
                        # Convert to RGB (assuming CNN expects RGB)
                        crop_rgb = cv2.cvtColor(crop, cv2.COLOR_BGR2RGB)
                        # Resize to 48x48
                        resized = cv2.resize(crop_rgb, (48, 48))
                        # Normalize
                        normalized = resized.astype(np.float32) / 255.0
                        # Add batch dimension
                        input_data = np.expand_dims(normalized, axis=0)
                        # Set input tensor for TFLite
                        interpreter.set_tensor(input_details[0]['index'], input_data)
                        # Run inference
                        interpreter.invoke()
                        # Get output
                        prediction = interpreter.get_tensor(output_details[0]['index'])
                        class_id = np.argmax(prediction)
                        label = classes[class_id]
                        prob = prediction[0][class_id]
                        # Draw bounding box and label
                        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        cv2.putText(frame, f"{label} {prob:.2f}", (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

    # Display the frame
    cv2.imshow('Real-Time Traffic Sign Detection and Classification', frame)

    # Quit on 'q' key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()