using System.Collections;
using System.Collections.Generic;
using System.Data;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
 public CharacterController characterController;
 // Скорость ходьбы - регулируется в Inspector
 public float speed = 6f;
 // Высота прыжка - регулируется в Inspector
 public float jumpHeight = 1.0f;
 // Камера
 public Transform cameraHolder;
 // Чувствительность мыши - регулируется в Inspector
 public float mouseSensivity = 2f;
 // Ограничения взгляда вверх и вниз - регулируются в Inspector
 public float upLimit = -50;
 public float downLimit = 50;
 // Гравитация
 private float gravityValue = -9.87f;
 // Стоит ли игрок на земле
 private bool groundedPlayer;
 // Скорость свободного перемещения игрока (по Y)
 private Vector3 playerVelocity;
 void Start()
 {
 // Скрыть курсор мыши с экрана
 Cursor.visible = false;
 }
 void Update()
 {
 Move();
 Rotate();
 Jump();
 }
 // --ПЕРЕМЕЩЕНИЕ--
 private void Move()
 {
 float horizontalMove = Input.GetAxis("Horizontal");
 float verticalMove = Input.GetAxis("Vertical");
 // Если персонаж стоит на земле, убрать скорость
 groundedPlayer = characterController.isGrounded;
 if (groundedPlayer && playerVelocity.y < 0) playerVelocity.y = 0f;
 else playerVelocity.y += gravityValue * Time.deltaTime;
 Vector3 gravityMove = new Vector3(0, playerVelocity.y, 0);
 Vector3 move = transform.forward * verticalMove + transform.right *
horizontalMove;
 characterController.Move(speed * Time.deltaTime * move + gravityMove *
Time.deltaTime);
 }
 // --ВРАЩЕНИЕ КАМЕРЫ--
 private void Rotate()
 {
 float horizontalRotation = Input.GetAxis("Mouse X");
 float verticalRotation = Input.GetAxis("Mouse Y");
 transform.Rotate(0, horizontalRotation * mouseSensivity, 0);
 cameraHolder.Rotate(-verticalRotation * mouseSensivity, 0, 0);
 Vector3 currentRotation = cameraHolder.localEulerAngles;
 if (currentRotation.x > 180) currentRotation.x -= 360;
 currentRotation.x = Mathf.Clamp(currentRotation.x, upLimit, downLimit);
 cameraHolder.localRotation = Quaternion.Euler(currentRotation);
 }
 // --ПРЫЖКИ--
 private void Jump()
 {
 // Если персонаж стоит на земле, убрать скорость
 groundedPlayer = characterController.isGrounded;
 if (groundedPlayer && playerVelocity.y < 0) playerVelocity.y = 0f;
 // Если нажат пробел, и персонаж стоит на земле, вычисляется скорость прыжка
 if (Input.GetKey(KeyCode.Space) && groundedPlayer)
 {
 playerVelocity.y += Mathf.Sqrt(jumpHeight * -2.0f * gravityValue);
 }
 // Перемещение персонажа по оси Y (прыжок)
 playerVelocity.y += gravityValue * Time.deltaTime;
 characterController.Move(playerVelocity * Time.deltaTime);
 }
}