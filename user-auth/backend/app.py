from flask import Flask, abort, jsonify, request, session
from config import ApplicationConfig
from models import db, User

from flask_cors import CORS

from flask_jwt_extended import create_access_token
from flask_jwt_extended import get_jwt_identity
from flask_jwt_extended import jwt_required
from flask_jwt_extended import JWTManager

app = Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'

# Setup the Flask-JWT-Extended extension
app.config["JWT_SECRET_KEY"] = "super-secret"
jwt = JWTManager(app)
CORS(app, supports_credentials=True, origins=["http://localhost:5173"])
db.init_app(app)

with app.app_context():
    db.create_all()


@app.route("/token", methods=["POST"])
def create_token():
    email = request.json.get("email", None)
    password = request.json.get("password", None)
    user = User.query.filter_by(email=email).first()


    if not user:
        return jsonify({"error": "Invalid email or password"}), 401
    
    access_token = create_access_token(identity=email)
    return jsonify(access_token=access_token)

@app.route("/register", methods=["POST"])
def register():
    email = request.json.get("email", None)
    password = request.json.get("password", None)

    if not email or not password:
        return jsonify({"error": "Email and password are required"}), 400
    
    if User.query.filter_by(email=email).first():
        return jsonify({"error": "Email already exists"}), 400

    new_user = User(email=email, password=password)
    db.session.add(new_user)
    db.session.commit()
    access_token = create_access_token(identity=email)
    return jsonify(access_token=access_token)

@app.route("/test")
def test():
    test = User.query.filter_by(email="test").first()
    if not test:
        return "no"
    return test.email


@app.route("/message", methods=["GET"])
@jwt_required()
def message():
    return jsonify({"hello": "hi"}), 200

if __name__ == "__main__":
    app.run(debug=True, host="127.0.0.1", port=5000)