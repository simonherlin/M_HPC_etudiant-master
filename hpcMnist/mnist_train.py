import tensorflow.keras as kr

(x_train, y_train), (x_test, y_test) = kr.datasets.mnist.load_data()

x_train = x_train.reshape(x_train.shape[0], 28, 28, 1).astype('float32')
x_test = x_test.reshape(x_test.shape[0], 28, 28, 1).astype('float32')

x_train /= 255
x_test /= 255

y_train = kr.utils.to_categorical(y_train, 10)
y_test = kr.utils.to_categorical(y_test, 10)

model = kr.models.Sequential()
model.add(kr.layers.Conv2D(32, (3, 3), input_shape=(28, 28, 1)))
model.add(kr.layers.Activation('relu'))
model.add(kr.layers.MaxPooling2D(pool_size=(2, 2)))
model.add(kr.layers.Flatten())
model.add(kr.layers.BatchNormalization())
model.add(kr.layers.Dense(256))
model.add(kr.layers.Activation('relu'))
model.add(kr.layers.Dropout(0.2))
model.add(kr.layers.Dense(10))
model.add(kr.layers.Activation('softmax'))

model.compile(loss='categorical_crossentropy', optimizer=kr.optimizers.Adam(), metrics=['accuracy'])

model.fit(x_train, y_train, batch_size=64, epochs=3, validation_data=(x_test, y_test))

score = model.evaluate(x_test, y_test)
print(score)

model.save('mnist_model.h5')

