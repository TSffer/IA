from keras.applications.resnet50 import ResNet50
from keras.preprocessing import image
from keras.applications.resnet50 import preprocess_input, decode_predictions
import keras
import keras.utils
from keras import utils as np_utils
import numpy as np

model = keras.applications.ResNet50(include_top=True, weights='imagenet', input_tensor=None, input_shape=None, pooling=None, classes=1000)
#model = keras.applications.resnet.ResNet101(include_top=True, weights='imagenet', input_tensor=None, input_shape=None, pooling=None, classes=1000)
#model = keras.applications.resnet_v2.ResNet50V2(include_top=True, weights='imagenet', input_tensor=None, input_shape=None, pooling=None, classes=1000)
img_path = '/home/luis/Documentos/IA/keras/perro.jpeg'
img = image.load_img(img_path, target_size = (224,224))
x = image.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

#k = n
#print(k.shape)

preds = model.predict(x)

#model.predict(np.array(x))
#prediction = model.predict(np.array(x))

print('Predicted:', decode_predictions(preds, top=3)[0])